/**
 * Based on code example from RPi SDK
 * adapted by John Lamb
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "font.h"

#define IS_RGBW false   // Glowbit uses WS2812B RGB 8 bits each ie 24 bits
#define NUM_PIXELS 64   // Glowbit Matrix 8x8 uses an 8x8 matrix
#define SPACE_CHAR 0x20

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 2 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 2
#endif

uint32_t display_buffer [NUM_PIXELS];

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

void pattern_black(uint len, uint t){
   for (int i = 0; i < len; ++i)
        display_buffer[i] = 0;
}

void show(){
       for (int i = 0; i < NUM_PIXELS; ++i)
        put_pixel(display_buffer[i]);
}


    
void drawChar (char ch){
    if (ch>127) ch='.';
    int fMapOffset = (ch - SPACE_CHAR)*8;
    int display_cursorX = 0;
    for (int i=fMapOffset; i < fMapOffset+8; i++){
        int8_t column = fontmap[i];
        for (int display_cursorY = 0; display_cursorY<8; display_cursorY++){
            bool pixel = (column << display_cursorY) & 0b10000000;
            display_buffer[display_cursorX+(7-display_cursorY)*8] = pixel ? urgb_u32(0x50, 0x50, 0x50) : 0;
        }
    display_cursorX ++;
    display_cursorX %= 8;
    }
}

void scrollText(char* text){
    int xDone = 0;
    while (text[xDone/8]){
        char currentChar = text[xDone/8];
        if (currentChar>127) currentChar='.';
        int columnIndex = xDone % 8;
        int fMapOffset = (currentChar - SPACE_CHAR)*8 + columnIndex;
        for (int display_cursorY = 0; display_cursorY<8; display_cursorY++){
            bool pixel = (columnIndex << display_cursorY) & 0b10000000;
            display_buffer[7+(7-display_cursorY)*8] = pixel ? urgb_u32(0x50, 0x50, 0x50) : 0;
        }
        show();
        sleep_ms(250);
        xDone++;
    }
}

int main() {
    stdio_init_all();
    printf("WS2812B using GPIO %d\n", WS2812_PIN);

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    while (1) {
        pattern_black(NUM_PIXELS, 0);
        show();
        sleep_ms(500);
        scrollText("Hello World!");
        show();
        sleep_ms(500);
    }
}
