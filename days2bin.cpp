/**
 * Based on code example from RPi SDK
 * adapted by John Lamb
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"

#include "peripherals/busscan.h"
#include "flash/flash_utils.h"

#include "peripherals/SimpleDS3231_new.hpp"
#include "peripherals/glowbit.hpp"
#include "days2bin.hpp"
#include "access_point.h"

int main()
{
    // First we have to take over from the pushbutton keep the PICO powered until
    // we want to shut down.
    gpio_init(stay_powered_on_PIN);
    gpio_set_dir(stay_powered_on_PIN, GPIO_OUT);
    gpio_put(stay_powered_on_PIN, 1);




    
    stdio_init_all();

    for (int i=0;i<5;i++){
        sleep_ms(500);
        printf("Starting ...\n");
    }
 
    SimpleDS3231 rtc(DS3231_SDA_PIN, DS3231_SCL_PIN);
    glowbit_init();

    // for debugging and development only
    // make_test_data();
    // write_flash();

    struct Bin_Info *bi = read_flash();

    for (int i = 0; i < NUM_BIN_KINDS + 1; i++)
    {
        printf("Bintype %d: day: %d month: %d year: %d Interval: %d\n", i, bi[i].dd, bi[i].mm, bi[i].yy, bi[i].interval);
    }

    //rtc.set_time( 20, 06,  0, false, true);
    //rtc.set_date(17,1,2024);

    printf("\r%s -- %s -- %dC\n", rtc.get_date_str(), rtc.get_time_str(), rtc.get_temp());

     int result = access_point();
     printf("access_point result: %d\n", result); // shouldn't get here as access_point is infinite loop

    int dtc[NUM_BIN_KINDS];
    getDaysToCollection(dtc, rtc.get_year(), rtc.get_mon(), rtc.get_day());

    for (int j = 0; j < 4; j++)
    {

        for (int i = 0; i < NUM_BIN_KINDS; i++)
        {
            char s[10] = {};
            sprintf(s, "%d", dtc[i]);
            int r = 0;
            int g = 0;
            int b = 0;
            switch (i)
            {
            case 0:
                r = 0x30;
                break;
            case 1:
                r = 0x30;
                g = 0x30;
                break;
            case 2:
                g = 0x30;
                break;
            }
            if (dtc[i] > 0)
                scrollText(s, r, g, b);
        };
    };
    // Power down
    gpio_put(stay_powered_on_PIN, 0);
    sleep_ms(500); // This seems to be necessary to keep the gpio low long enough to power down
}