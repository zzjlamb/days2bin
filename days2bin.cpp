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

#include "peripherals/SimpleDS3231.hpp"
#include "peripherals/glowbit.hpp"
#include "days2bin.hpp"


int main()
{
    // First we have to take over from the pushbutton keep the PICO powered until
    // we want to shut down.
    gpio_init(stay_powered_on_PIN);
    gpio_set_dir(stay_powered_on_PIN, GPIO_OUT);
    gpio_put(stay_powered_on_PIN, 1);

    SimpleDS3231 rtc;
    stdio_init_all();

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

    //rtc.set_time( 20,  18,  0, false, true);
    //rtc.set_date(10,1,2024);

    printf("\r%s -- %s -- %dC\n", rtc.get_date_str(), rtc.get_time_str(), rtc.get_temp());

    glowbit_init();
    char s [100] = {}; 
    sprintf(s,"\r%s -- %s -- %dC\n", rtc.get_date_str(), rtc.get_time_str(), rtc.get_temp());
    scrollText(s);

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