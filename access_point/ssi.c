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
    "<html>\n"
    "<head>\n"
    "<meta http-equiv=\"refresh\" content=\"0; url='/index.shtml'\" />\n"
    "</head>"
    "<body>"
    "<p>You will be redirected to Days2Bin soon!</p>"
    "</body>"
    "</html>";

int fs_open_custom(struct fs_file *file, const char *name)
{
    printf("%s\n", name);
    return 0;
}


/*
int fs_read_custom(struct fs_file *file, char *buffer, int count) {
printf("fs_read_custom. Count: %d\n",count);
return 0;
}
*/


void fs_close_custom(struct fs_file *file)
{

}
