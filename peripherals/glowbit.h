#ifndef GLOWBIT_H
#define GLOWBIT_H

#ifdef __cplusplus
extern "C" {
#endif

void glowbit_init();
void drawChar(char ch, uint8_t r, uint8_t g, uint8_t b);
void scrollText(char * text, uint8_t r, uint8_t g, uint8_t b);

#ifdef __cplusplus
}
#endif

#endif