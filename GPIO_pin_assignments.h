
#pragma once

#define PowerOnButtonGPIO 9   // Low if button pressed
#define DS3231_SDA_PIN 16     // I2C SDA
#define DS3231_SCL_PIN 17     // I2C SCL
#define WS2812_PIN 18         // GPIO connected to Glowbit DIN terminal
#define stay_powered_on_PIN 8 // high to keep MOSFETs switched on, low to turn self off
