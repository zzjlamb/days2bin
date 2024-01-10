#ifndef GLOWBIT_HPP
#define GLOWBIT_HPP

#define WS2812_PIN 18            // GPIO connected to Glowbit DIN terminal
#include <string>

void glowbit_init();
void scrollText(std::string text);

#endif