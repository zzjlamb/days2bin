#ifndef GLOWBIT_H
#define GLOWBIT_H

#ifdef __cplusplus
extern "C"
{
#endif

    static uint32_t glowbit_GREEN = 0x00300000;
    static uint32_t glowbit_RED = 0x00003000;
    static uint32_t glowbit_BLUE = 0x00000030;
    static uint32_t glowbit_YELLOW = 0x00000030;

    void glowbit_init();
    void glowbit_show();
    void glowbit_clearScreen();
    void glowbit_drawChar(char ch, uint32_t colour);
    void glowbit_scrollText(char *text, uint32_t colour);

#ifdef __cplusplus
}
#endif

#endif