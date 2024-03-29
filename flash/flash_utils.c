/*
Utilities for writing and reading to flash

Our target sector is 4k from xb_offset +

*/

#include "flash_utils.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/flash.h"
#include <hardware/sync.h>
#include "time.h"
#include <math.h>

/* Compile variable set by custom linker script                 */
/* Points to a 4k block of memory reserved for persistent data  */
/* i.e. the bin collection date and frequency info              */

extern char ADDR_PERSISTENT;

Bin_Info binsData[NUM_BIN_KINDS + 1] = {};

void *getAddressPersistent()
{
    return &ADDR_PERSISTENT;
}

/* Populate the binsData array with some test settings */

void make_test_data()
{
    binsData[RED_BIN].dd = 11;
    binsData[RED_BIN].mm = 1;
    binsData[RED_BIN].yy = 24;
    binsData[RED_BIN].interval = 1;

    binsData[YELLOW_BIN].dd = 11;
    binsData[YELLOW_BIN].mm = 1;
    binsData[YELLOW_BIN].yy = 24;
    binsData[YELLOW_BIN].interval = 2;

    binsData[GREEN_BIN].interval = 0;

    binsData[MAGIC_NUMBER_BIN].interval = MAGIC_NUMBER;
}

/* Write the settings data to flash */

void write_flash()
{
    uint8_t buf[FLASH_PAGE_SIZE] = {};

    uint8_t *binsDataPtr = (uint8_t *)&binsData;
    for (int i = 0; i < sizeof(binsData); i++)
    {
        buf[i] = binsDataPtr[i];
    }

    uint8_t *ap = &ADDR_PERSISTENT;
    uint32_t xb = XIP_BASE;
    uint32_t xb_offset = (uint32_t)ap - xb;

    /* We need to save and disable interupts while writing flash */

    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(xb_offset, FLASH_SECTOR_SIZE);
    flash_range_program(xb_offset, buf, FLASH_PAGE_SIZE);
    restore_interrupts(ints);
}

Bin_Info *read_flash()
{
    void *ap = &ADDR_PERSISTENT;
    return ap;
}

/*  Fill an array of int - one for each bin type    */
/*  -1 means no collection for that bin colour      */

void getDaysToCollection(int dayArray[NUM_BIN_KINDS], uint8_t clock_century, uint8_t clock_yy, uint8_t clock_mm, uint8_t clock_dd)
{
    // TODO #### validate rtc date values
    struct tm clocktime = {};
    clocktime.tm_mday = clock_dd;
    clocktime.tm_mon = clock_mm - 1;
    clocktime.tm_year = (clock_century * 100) + clock_yy;
    time_t clocktime_tm = mktime(&clocktime);

    struct Bin_Info *bd = read_flash();
    for (int bt = 0; bt < NUM_BIN_KINDS; bt++)
    {
        if (bd[bt].interval == 0)
        {
            dayArray[bt] = -1;
        }
        else
        {
            /* Calculate the interval in days */
            
            struct tm bintime = {};
            bintime.tm_mday = bd[bt].dd;            // tm day of month is 1-31
            bintime.tm_mon = bd[bt].mm - 1;         // tm month is from 0-11
            bintime.tm_year = bd[bt].yy + 100;      // Convert from yy to years since 1900
            time_t bintime_tm = mktime(&bintime);
            double dd = difftime(clocktime_tm, bintime_tm);
            double ddDays = dd / (3600 * 24);
            int btInt = round(ddDays);
            int intvl = bd[bt].interval * 7;
            int mod_intvl = btInt % intvl;
            dayArray[bt] = (mod_intvl >= 0) ? intvl - mod_intvl : -mod_intvl;
        }
    }
}