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

#include "flash/flash_utils.h"

#include "peripherals/glowbit.h"
#include "ds3231.h"
#include "GPIO_pin_assignments.h"
#include "access_point.h"

// DS3231 real time clock
ds3231_t ds3231;

int main()
{
    // First we have to take over from the pushbutton keep the PICO powered until
    // we want to shut down.
    gpio_init(stay_powered_on_PIN);
    gpio_set_dir(stay_powered_on_PIN, GPIO_OUT);
    gpio_put(stay_powered_on_PIN, 1);

    gpio_init(PowerOnButtonGPIO);
    gpio_set_dir(PowerOnButtonGPIO, GPIO_IN);

    stdio_init_all();
    sleep_ms(200);

    /* Initialise ds3231 struct. */
    ds3231_init(&ds3231, i2c_default, DS3231_DEVICE_ADRESS, AT24C32_EEPROM_ADRESS_0);

    sleep_ms(200);
    /* Initialise I2C line. */
    gpio_init(DS3231_SDA_PIN);
    gpio_init(DS3231_SCL_PIN);
    gpio_set_function(DS3231_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(DS3231_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(DS3231_SDA_PIN);
    gpio_pull_up(DS3231_SCL_PIN);
    i2c_init(ds3231.i2c, 400 * 1000);

    glowbit_init();

    // for debugging and development only
    // make_test_data();
    // write_flash();

    Bin_Info *bi = read_flash();

    /* Read the time registers of DS3231. */
    ds3231_data_t ds3231_data = {};
    if (ds3231_read_current_time(&ds3231, &ds3231_data))
    {
        printf("No data received from DS3231\n");
    }
    else
    {
        printf("%02u:%02u:%02u    %10s    %02u/%02u/20%02u\n",
               ds3231_data.hours, ds3231_data.minutes, ds3231_data.seconds,
               ds3231_data.date, ds3231_data.month, ds3231_data.year);
    }

    for (int i = 0; i < NUM_BIN_KINDS + 1; i++)
    {
        printf("Bintype %d: day: %d month: %d year: %d Interval: %d\n", i, bi[i].dd, bi[i].mm, bi[i].yy, bi[i].interval);
    }

    int dtc[NUM_BIN_KINDS];
    getDaysToCollection(dtc, ds3231_data.century, ds3231_data.year, ds3231_data.month, ds3231_data.date);

    for (int j = 0; j < 2; j++)
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

    // Is the power on button still on?
    // If so start web server and await new settings
    if (!gpio_get(PowerOnButtonGPIO))
        {
            drawChar('~', 0, 0, 0x30); // wifi symbol
            // access_point();
        }

    // Power down
    gpio_put(stay_powered_on_PIN, 0);
    sleep_ms(500); // This seems to be necessary to keep the gpio low long enough to power down
}