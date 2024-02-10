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

// DS3231 real time clock
ds3231_t ds3231;

int main()
{
    // First we have to take over from the pushbutton keep the PICO powered until
    // we want to shut down.
    power_mgr_init();

    stdio_init_all();
    sleep_ms(200);

    adc_init();
    adc_set_temp_sensor_enabled(true);

// Pico W uses a CYW43 pin to get VBUS so we need to initialise it
#if CYW43_USES_VSYS_PIN
    if (cyw43_arch_init())
    {
        printf("failed to initialise\n");
        return 1;
    }
#endif

    bool old_battery_status;
    float old_voltage;
    bool battery_status = true;
    char *power_str = "UNKNOWN";

    // Get battery status
    if (power_source(&battery_status) == PICO_OK)
    {
        power_str = battery_status ? "BATTERY" : "POWERED";
    }

    // Get voltage
    float voltage = 0;
    int voltage_return = power_voltage(&voltage);
    voltage = floorf(voltage * 100) / 100;

    // Also get the temperature
    adc_select_input(4);
    const float conversionFactor = 3.3f / (1 << 12);
    float adc = (float)adc_read() * conversionFactor;
    float tempC = 27.0f - (adc - 0.706f) / 0.001721f;

#if CYW43_USES_VSYS_PIN
    cyw43_arch_deinit();
#endif

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

    /* Initialise glowbit matrix */
    glowbit_init();

    /* For debugging and development only */
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
        printf("%02u:%02u:%02u %02u/%02u/20%02u\n",
               ds3231_data.hours, ds3231_data.minutes, ds3231_data.seconds,
               ds3231_data.date, ds3231_data.month, ds3231_data.year);
    }

    for (int i = 0; i < NUM_BIN_KINDS + 1; i++)
    {
        printf("Bintype %d: day: %d month: %d year: %d Interval: %d\n", i, bi[i].dd, bi[i].mm, bi[i].yy, bi[i].interval);
    }

    if (bi[NUM_BIN_KINDS].interval == MAGIC_NUMBER)
    {
        // Here if already set up
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
        glowbit_scrollText("Keep pressing lid to set up ...", glowbit_BLUE);
    }

    // Is the power on button still on?
    // If so start web server and await new settings
    if (!gpio_get(PowerOnButtonGPIO))
    {
        glowbit_scrollText("Join Days2Bin on WiFi ...", glowbit_BLUE);
        glowbit_drawChar('~', glowbit_BLUE); // wifi symbol
        glowbit_show();
        access_point();
    }
    else
    {
        // Power down
        power_mgr_shutDownNow();
    }
}