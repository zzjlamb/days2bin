/**
 * Days2Bin
 * An indicator to show number of days until different kerbside
 * bins/trash/recycling etc are due to be collected.
 *
 * Hardware - Raspberry Pi Pico W, DS3231 RTC and
 * Core Electronics GlowBit (based on WS2812 addressable LEDs).
 *
 * The device is powered on by a pair of logic level MOSFETs
 * triggered by grounding via a momentary pushbutton, and kept alive
 * by one of the Pico W GPIO's.
 *
 * 2024 by John Lamb
 * Licenced under MIT Licence
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include "pico/float.h"

#include <power_status.h>

#include "flash/flash_utils.h"
#include "peripherals/glowbit.h"
#include "ds3231.h"
#include "GPIO_pin_assignments.h"
#include "peripherals/power_mgr.h"
#include "access_point.h"

/* Globals */

ds3231_t ds3231;                    // DS3231 real time clock
char batteryVoltageStr [8]={};      // Battery voltage

int main()
{
    /* First we have to take over from the pushbutton keep the PICO powered until   */ 
    /* we want to shut down.                                                        */

    power_mgr_init();

    /* Initialise coms for debug messages, and wait to stabilise   */

    stdio_init_all();
    sleep_ms(200);

    /* Initialise the ADC so we can check battery voltage */

    adc_init();

    /* Pico W uses a CYW43 pin to get VBUS so we need to initialise it.                 */
    /* The same pin is used for wi-fi so we need to check the voltage then de-init      */
    /* before the webserver runs.                                                       */

    if (!cyw43_arch_init())
    {
        // Get voltage
        float voltage;
        int voltage_return = power_voltage(&voltage);
        voltage = floorf(voltage * 100) / 100;
        snprintf(batteryVoltageStr,sizeof(batteryVoltageStr),"%.2f",voltage);
        cyw43_arch_deinit();
    }

    /* Initialise ds3231 struct. */

    ds3231_init(&ds3231, i2c_default, DS3231_DEVICE_ADRESS, AT24C32_EEPROM_ADRESS_0);
    sleep_ms(200);

    /* Initialise I2C for the DS3231. */

    gpio_init(DS3231_SDA_PIN);
    gpio_init(DS3231_SCL_PIN);
    gpio_set_function(DS3231_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(DS3231_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(DS3231_SDA_PIN);
    gpio_pull_up(DS3231_SCL_PIN);
    i2c_init(ds3231.i2c, 400 * 1000);

    /* Initialise Glowbit matrix */

    glowbit_init();

    /* For debugging and development only */
    // make_test_data();
    // write_flash();

    /* Get a pointer to the reserved flash page where   */
    /* our settings are stored.                         */

    Bin_Info *bi = read_flash();

    /* Get the date and time from the DS3231. */

    ds3231_data_t ds3231_data = {};
    ds3231_read_current_time(&ds3231, &ds3231_data);

    if ( (bi[NUM_BIN_KINDS].interval == MAGIC_NUMBER) || (ds3231_data.year==0) )
    {
        /* Here if already set up, ie Magic number in flash, and DS3231 has a non-zero year. */ 

        int dtc[NUM_BIN_KINDS];
        getDaysToCollection(dtc, ds3231_data.century, ds3231_data.year, ds3231_data.month, ds3231_data.date);
        uint32_t binColours[] = {glowbit_RED, glowbit_YELLOW, glowbit_GREEN};
        for (int j = 0; j < 2; j++)
        {
            for (int i = 0; i < NUM_BIN_KINDS; i++)
            {
                char s[10] = {};
                sprintf(s, "%d", dtc[i]);
                uint32_t colour;
                if (dtc[i] > 0)
                    glowbit_scrollText(s, binColours[i]);
            };
        };
    }
    else
    {
        /* Here if no magic number or an invalid date, so prompt to enter set up mode           */
        /* This will occur for first time use, or if RTC battery has failed or been replaced.   */

        glowbit_scrollText("Keep pressing lid to set up ...", glowbit_BLUE);
    }

    /* Is the power on button still on?                 */
    /* If so start web server and await new settings    */ 

    if (!gpio_get(PowerOnButtonGPIO))
    {
        glowbit_scrollText("Join Days2Bin WiFi ...", glowbit_BLUE);
        glowbit_drawChar('~', glowbit_BLUE); // wifi symbol
        glowbit_show();
        access_point();
    }
    else        /* Power down */
    {
        power_mgr_shutDownNow();
    }
}