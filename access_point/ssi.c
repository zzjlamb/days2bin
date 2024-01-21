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
    if (strcmp(name,"/hotspot-detect.html")){
        return 0;
    }
    // Here if the requested file is "/hotspot-detect.html"
    printf("%s\n", name);
        /* initialize fs_file correctly */
    memset(file, 0, sizeof(struct fs_file));
    file->pextension = mem_malloc(sizeof(redirect_html));
    if (file->pextension != NULL) {
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

void
fs_close_custom(struct fs_file *file)
{
  if (file && file->pextension) {
    mem_free(file->pextension);
    file->pextension = NULL;
  }
}
