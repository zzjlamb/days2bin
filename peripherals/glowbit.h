#ifndef GLOWBIT_H
#define GLOWBIT_H

#ifdef __cplusplus
extern "C"
{
#endif

    #define glowbit_GREEN 0x00300000
    #define glowbit_RED 0x00003000
    #define glowbit_BLUE 0x00000030
    #define glowbit_YELLOW glowbit_RED | glowbit_GREEN

    void glowbit_init();
    void glowbit_show();
    void glowbit_clearScreen();
    void glowbit_drawChar(char ch, uint32_t colour);
    void glowbit_scrollText(char *text, uint32_t colour);

#ifdef __cplusplus
}
#endif

#endif