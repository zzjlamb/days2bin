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

#include "hardware/clocks.h"

#include "peripherals/busscan.h"
#include "flash/flash_utils.h"

#include "peripherals/SimpleDS3231_new.hpp"
#include "peripherals/glowbit.hpp"
#include "days2bin.hpp"

int main()
{
    // First we have to take over from the pushbutton keep the PICO powered until
    // we want to shut down.
    gpio_init(stay_powered_on_PIN);
    gpio_set_dir(stay_powered_on_PIN, GPIO_OUT);
    gpio_put(stay_powered_on_PIN, 1);

    SimpleDS3231 rtc(DS3231_SDA_PIN, DS3231_SCL_PIN);
    stdio_init_all();
    glowbit_init();

    /*
    //for debugging and development only
    make_test_data();
    write_flash();
    */

    struct Bin_Info *bi = read_flash();

    for (int i = 0; i < NUM_BIN_KINDS; i++)
    {
        printf("Bintype %d: day: %d month: %d year: %d Interval: %d\n", i, bi[i].dd, bi[i].mm, bi[i].yy, bi[i].interval);
    }

    //rtc.set_time( 21,  18,  0, false, true);
   // rtc.set_date(12,1,2024);

    printf("\r%s -- %s -- %dC\n", rtc.get_date_str(), rtc.get_time_str(), rtc.get_temp());

    int dtc[NUM_BIN_KINDS];
    getDaysToCollection(dtc, rtc.get_year(),rtc.get_mon(),rtc.get_day());
    

    while (0)
    {
        char s[100] = {};
        sprintf(s, "\r%s -- %s -- %dC\n", rtc.get_date_str(), rtc.get_time_str(), rtc.get_temp());
        printf("%s\n", s);
        scrollText(s,0x40, 0, 0);
    };

    /*
        while (0)
        {
            clearScreen();
            sleep_ms(500);
            char aNumberString[20];
            printf("%s %dC\n", rtc.get_time_str(), rtc.get_temp());
            snprintf(aNumberString, 16, "%s %dC", rtc.get_time_str(), rtc.get_temp());
            scrollText(aNumberString);

            sleep_ms(500);
        }
    */
}