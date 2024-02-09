#ifndef GLOWBIT_HPP
#define GLOWBIT_HPP

#ifdef __cplusplus
extern "C" {
#endif

#define WS2812_PIN 18            // GPIO connected to Glowbit DIN terminal

void glowbit_init();
void scrollText(char * text, uint8_t r, uint8_t g, uint8_t b);

#ifdef __cplusplus
}
#endif

#endif