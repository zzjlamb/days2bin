/**
 * Based on code example from RPi SDK
 * adapted by John Lamb
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "ws2812.pio.h"

#include "font.hpp"

#include "busscan.h"
#include "flash/flash_utils.h"

#include "SimpleDS3231.hpp"

#define IS_RGBW false // Glowbit uses WS2812B RGB 8 bits each ie 24 bits
#define NUM_PIXELS 64 // Glowbit Matrix 8x8 uses an 8x8 matrix
#define NUM_COLUMNS 8
#define NUM_ROWS 8
#define SPACE_CHAR 0x20

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 2 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 2
#endif

uint32_t display_buffer[NUM_ROWS][NUM_COLUMNS];

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) |
           ((uint32_t)(g) << 16) |
           (uint32_t)(b);
}

void pattern_black()
{
    for (int i = 0; i < NUM_ROWS; ++i)
        for (int j = 0; j < NUM_COLUMNS; j++)
            display_buffer[i][j] = 0;
}

void show()
{
    for (int i = 0; i < NUM_ROWS; ++i)
        for (int j = 0; j < NUM_COLUMNS; j++)
            put_pixel(display_buffer[i][j]);
}

void clearScreen()
{
    pattern_black();
    show();
}

void drawChar(char ch)
{
    if (ch > 127)
        ch = '.';
    int fMapOffset = (ch - SPACE_CHAR) * 8;
    int display_cursorX = 0;
    for (int i = fMapOffset; i < fMapOffset + 8; i++)
    {
        int8_t column = fontmap[i];
        for (int display_cursorY = 0; display_cursorY < 8; display_cursorY++)
        {
            bool pixel = (column << display_cursorY) & 0b10000000;
            display_buffer[(7 - display_cursorY) * 8][display_cursorX] = pixel ? urgb_u32(0x40, 0x40, 0x40) : 0;
        }
        display_cursorX++;
        display_cursorX %= 8;
    }
}

void scrollText(std::string text)
{
    int textLength = text.length();

    // do nothing if null string
    if (textLength==0)
        return;
    
    // repeat code below eight times for each character, including the terminating null
    for (int xDone=0;xDone<(textLength+1)*8;xDone++){

        // Shift one column to left
        for (int x = 1; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                display_buffer[y][x - 1] = display_buffer[y][x];
            }
        }
        char currentChar = text[xDone / 8];
        if (currentChar == 0)
            currentChar = SPACE_CHAR; // to flush last character in string off the display
        
        if (currentChar > 127)
            currentChar = '.';  // render out of range char as a '.'

        int columnIndex = xDone % 8;
        int fMapOffset = (currentChar - SPACE_CHAR) * 8 + columnIndex;
        int8_t column = fontmap[fMapOffset];
        for (int display_cursorY = 0; display_cursorY < 8; display_cursorY++)
        {
            bool pixel = (column << display_cursorY) & 0b10000000;
            display_buffer[7 - display_cursorY][7] = pixel ? urgb_u32(0x50, 0x50, 0x50) : 0;
        }
        show();
        sleep_ms(100);
    }
}

int main()
{
    SimpleDS3231 rtc;
    stdio_init_all();

    make_test_data();
    write_flash();

    printf("WS2812B using GPIO %d\n", WS2812_PIN);

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    // bus_scan();

    while(0){
        printf("\r%s -- %s -- %d%cC", rtc.get_date_str(), rtc.get_time_str(), rtc.get_temp());
        sleep_ms(500);
    }

    

    /*rtc.set_sec(0);
    rtc.set_hou(20, false, true);
    rtc.set_min(0);*/

    while (0)
    {
        clearScreen();
        sleep_ms(500);        
        char aNumberString [20];
        printf("%s %dC\n", rtc.get_time_str(), rtc.get_temp());
        snprintf(aNumberString, 16,"%s %dC", rtc.get_time_str(), rtc.get_temp());
        scrollText(aNumberString);
        
        

        sleep_ms(500);
    }
}
