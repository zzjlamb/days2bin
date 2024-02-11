#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "ssi.h"
#include "lwip/apps/fs.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/apps/fs.h"

#include "ds3231.h"
#include "flash/flash_utils.h"

extern ds3231_t ds3231;
extern char batteryVoltageStr[];

// max length of the tags defaults to be 8 chars
// LWIP_HTTPD_MAX_TAG_NAME_LEN
const char *__not_in_flash("httpd") ssi_example_tags[] = {
    "dttime",        // 0
    "binData",       // 1
    "batVolt" // 2
};

u16_t __time_critical_func(ssi_handler)(int iIndex, char *pcInsert, int iInsertLen)
{
    size_t printed;
    switch (iIndex)
    {
    case 0: /* dttime */
        // Return DS3231 time and date
        ds3231_data_t ds3231_data = {};
        ds3231_read_current_time(&ds3231, &ds3231_data);
        printed = snprintf(pcInsert, iInsertLen, "%02u:%02u %02u/%02u/20%02u\n",
                           ds3231_data.hours, ds3231_data.minutes,
                           ds3231_data.date, ds3231_data.month, ds3231_data.year);
        break;

    case 1: /*binData*/

        // Bin_Info is 4 x uint8_t packed, so should be safe to cast to array of uint_8
        uint8_t *bi = (uint8_t *)read_flash();

        // Check for magic number and generate 1 week for waste, 0 for others, and 000000 for dates
        //  to advise javascript on web page to make new dates
        //
        if (bi[NUM_BIN_KINDS * sizeof(Bin_Info)] == MAGIC_NUMBER)
        {
            // Encode bin data to iiyymmdd x3 format for web page java function
            int binDataLen = sizeof(Bin_Info) * NUM_BIN_KINDS; // Should be 12 i.e. less than expected iInsertLen of 192

            for (int i = 0; i < binDataLen; i++)
            {
                pcInsert[i * 2] = (bi[i] / 10) + '0';
                pcInsert[i * 2 + 1] = (bi[i] % 10) + '0';
            }
            pcInsert[binDataLen * 2 + 2] = 0;
            printed = binDataLen * 2;
        }
        else
        {
            /* This appears to be the first run. No data in flash yet. */
            printed = snprintf(pcInsert, iInsertLen, "010000000000000000000000");
        }

        break;

    case 2: /* batteryVoltage */
        // Return battery voltage (vSys)
        printed = snprintf(pcInsert, iInsertLen, batteryVoltageStr);
        break;

    default: /* unknown tag */
        printed = 0;
        break;
    }
    LWIP_ASSERT("sane length", printed <= 0xFFFF);
    return (u16_t)printed;
}

void ssi_init()
{

    size_t i;
    for (i = 0; i < LWIP_ARRAYSIZE(ssi_example_tags); i++)
    {
        LWIP_ASSERT("tag too long for LWIP_HTTPD_MAX_TAG_NAME_LEN",
                    strlen(ssi_example_tags[i]) <= LWIP_HTTPD_MAX_TAG_NAME_LEN);
    }

    http_set_ssi_handler(ssi_handler,
                         ssi_example_tags, LWIP_ARRAYSIZE(ssi_example_tags));
}

// Handlers for lwipopts.h LWIP_HTTPD_CUSTOM_FILES
// fs_open_custom is called before any other file handlers
//
// See https://github.com/particle-iot/lwip-contrib/blob/master/examples/httpd/genfiles_example/genfiles_example.c#L98
// for an example. We can use this for a redirect to index.shtml when the client tries one of the tags below
// Or, we could put a page in the fs c file with one of the names below with a redirect as it's content.
/*
    /hotspot-detect.html
    /404.html
    /404.htm
    /404.shtml
    /404.html
    /404.htm
    /404.shtml
*/

const char redirect_html[] =
    "HTTP/1.1 302 Redirect\n"
    "Location: http://192.168.4.1/index.shtml\n\n"
    "Server: lwIP/pre-0.6 (http://www.sics.se/~adam/lwip/)\n"
    "Content-type: text/html\n\n"
    "<!DOCTYPE html>"
    "<html>"
    "<meta http-equiv=\"Refresh\" content=\"0; url='http://192.168.4.1/index.shtml'\" />"
    "<head> <title>Pico W Redirect</title> </head>"
    "<body> <h1>Pico W Redirect</h1>"
    "<p>Redirecting to /index.shtml</p>"
    "</body>"
    "</html>";

// We need to treat this as a custom file because it has a "-" in the name
int fs_open_custom(struct fs_file *file, const char *name)
{
    if (strcmp(name, "/hotspot-detect.html"))
    {
        return 0;
    }
    // Here if the requested file is "/hotspot-detect.html"
    printf("%s\n", name);
    /* initialize fs_file correctly */
    memset(file, 0, sizeof(struct fs_file));
    file->pextension = mem_malloc(sizeof(redirect_html));
    if (file->pextension != NULL)
    {
        /* instead of doing memcpy, you would generate e.g. a JSON here */
        memcpy(file->pextension, redirect_html, sizeof(redirect_html));
        file->data = (const char *)file->pextension;
        file->len = sizeof(redirect_html) - 1; /* don't send the trailing 0 */
        file->index = file->len;
        /* allow persisting connections */
        file->flags = FS_FILE_FLAGS_HEADER_PERSISTENT || FS_FILE_FLAGS_HEADER_INCLUDED;
        return 1;
    }
}

void fs_close_custom(struct fs_file *file)
{
    if (file && file->pextension)
    {
        mem_free(file->pextension);
        file->pextension = NULL;
    }
}

// POST callbacks
// See https://lwip.nongnu.org/2_1_x/group__httpd.html#ga6cb33693ee8f0c054be82a968ceff582
//

err_t httpd_post_begin(void *connection, const char *uri, const char *http_request,
                       u16_t http_request_len, int content_len, char *response_uri,
                       u16_t response_uri_len, u8_t *post_auto_wnd)
{
    printf("httpd_post_begin called.\n");
    printf("URI: %S\n", uri);
    printf("http_request: %s\n", http_request);
    printf("http_request_len: %d\n", http_request_len);
    printf("content_len: %d\n");
    printf("response_uri: %s\n", response_uri);
    printf("response_uri_len: %d\n", response_uri_len);
    printf("post_auto_wnd: %d\n\n", post_auto_wnd);
    return ERR_OK;
}

err_t httpd_post_receive_data(void *connection, struct pbuf *p)
{
    printf("httpd_post_receive_data called. Length: %d\n", p->len);

    err_t ret_val = ERR_VAL;

    if (connection != NULL && p != NULL)
    {
        printf("pfuf payload: ");
        char *data = p->payload;
        int i = 0;
        while (i < p->len)
        {
            printf("%c", data[i]);
            i++;
        }
        printf("\n");
        ret_val = ERR_OK;
    }

    if (p != NULL)
    {
        pbuf_free(p);
    }
    return ret_val;
}

void httpd_post_finished(void *connection,
                         char *response_uri,
                         u16_t response_uri_len)
{
    printf("httpd_post_finished called.\n");
    strncpy(response_uri, "/index.shtml", response_uri_len);
}