#include "pico/stdlib.h"
#include "GPIO_pin_assignments.h"
#include "power_mgr.h"

// Turn stay_powered_on_PIN high to keep the power on after the user
// releases the On button
//
void power_mgr_init()
{
    gpio_init(stay_powered_on_PIN);
    gpio_set_dir(stay_powered_on_PIN, GPIO_OUT);
    gpio_put(stay_powered_on_PIN, 1);

    gpio_init(PowerOnButtonGPIO);
    gpio_set_dir(PowerOnButtonGPIO, GPIO_IN);
    gpio_set_pulls(PowerOnButtonGPIO, true, false);  // Pull up
}

// Turn of the power
//
void power_mgr_shutDownNow()
{
    gpio_put(stay_powered_on_PIN, 0);
    sleep_ms(500); // This seems to be necessary to keep the gpio low long enough to power down
}
