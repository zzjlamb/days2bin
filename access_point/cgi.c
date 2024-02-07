#include "lwip/apps/httpd.h"
#include "cgi.h"

// CGI handler which is run when a request for /led.cgi is detected
const char * cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    printf("cgi handler called with %d params. First param and value %s, %s",iNumParams,pcParam[0],pcValue[0]);
    // Send the index page back to the user
    return "/index.shtml";
}

// tCGI Struct
// Fill this with all of the CGI requests and their respective handlers
static const tCGI cgi_handlers[] = {
    {
        // Html request for "/update.cgi" triggers cgi_handler
        "/update.cgi", cgi_led_handler
    },
};

void cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers, 1);
}