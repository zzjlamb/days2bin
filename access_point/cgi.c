#include <string.h>
#include "lwip/apps/httpd.h"
#include "ds3231.h"
#include "cgi.h"
#include "flash/flash_utils.h"

extern ds3231_t ds3231;
extern Bin_Info binsData[];
extern bool powerDownAtNextPoll;

uint8_t char2ToByte(char *twoChars, int firstCharOffset)
{
    uint8_t rByte = twoChars[firstCharOffset] - '0';
    rByte *= 10;
    rByte += twoChars[firstCharOffset + 1] - '0';
    return rByte;
}

// CGI handler which is run when a request for /led.cgi is detected
const char *cgi_settings_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{

    for (int i = 0; i < iNumParams; i++)
    {
        if (!strcmp(pcParam[i], "clientDateTime"))
        {
            char *clientDateTime = pcValue[i];

            ds3231_data_t ds3231_data = {
                .seconds = char2ToByte(clientDateTime, 0),
                .minutes = char2ToByte(clientDateTime, 2),
                .hours = char2ToByte(clientDateTime, 4),
                .date = char2ToByte(clientDateTime, 6),
                .month = char2ToByte(clientDateTime, 8),
                .year = char2ToByte(clientDateTime, 10),
                .century = 1,
                .am_pm = false};

            ds3231_configure_time(&ds3231, &ds3231_data);
        }
        if ((!strcmp(pcParam[i], "binData")) && (strlen(pcValue[i]) == 2 * NUM_BIN_KINDS * sizeof(Bin_Info)))
        {
            // Here if parameter name is binData and value has the right number of characters
            uint8_t *bd = (uint8_t *)&binsData;
            for (int j = 0; j < NUM_BIN_KINDS * sizeof(Bin_Info); j++)
            {
                bd[j] = char2ToByte(pcValue[i], j * 2);
            }
            // Set the interval byte of the dummy appended Bin-Info to magic number
            // (ie next byte from the actual ones)
            binsData[NUM_BIN_KINDS].interval = MAGIC_NUMBER;
        }
    }
    for (int k = 0; k < NUM_BIN_KINDS + 1; k++)
    {
        printf("Bin type: %d Interval %d Year %d Month %d Day %d\n", k, binsData[k].interval, binsData[k].yy, binsData[k].mm, binsData[k].dd);
    }
    write_flash();

    // Power down at next poll
    powerDownAtNextPoll = true;

    // Send the index page back to the user
    return "/settingssaved.html";
}

// tCGI Struct
// Fill this with all of the CGI requests and their respective handlers
static const tCGI cgi_handlers[] = {
    // Html request for "/update.cgi" triggers cgi_handler
    { "/update.cgi", cgi_settings_handler},
};

void cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers, 1);
}