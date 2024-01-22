#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "ssi.h"
// #include "cgi.h"
#include "lwip/apps/fs.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/apps/fs.h"

// max length of the tags defaults to be 8 chars
// LWIP_HTTPD_MAX_TAG_NAME_LEN
const char *__not_in_flash("httpd") ssi_example_tags[] = {
    "dttime", // 0
    "binData" // 1
};

u16_t __time_critical_func(ssi_handler)(int iIndex, char *pcInsert, int iInsertLen)
{
    size_t printed;
    switch (iIndex)
    {
    case 0: /* dttime */
        printed = snprintf(pcInsert, iInsertLen, "Date Time Placeholder");
        break;
    case 1: /*binData*/
        printed = snprintf(pcInsert, iInsertLen, "binData placeholder");
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

/*
int fs_read_custom(struct fs_file *file, char *buffer, int count) {
printf("fs_read_custom. Count: %d\n",count);
return 0;
}
*/

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
/*void * 	connection,
const char * 	uri,
const char * 	http_request,
u16_t 	http_request_len,
int 	content_len,
char * 	response_uri,
u16_t 	response_uri_len,
u8_t * 	post_auto_wnd
*/
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
        int i=0;
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