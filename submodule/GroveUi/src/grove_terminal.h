#ifndef GROVE_UI_TERMINAL
#define GROVE_UI_TERMINAL
#include<stdint.h>
#define LCD_HEIGHT                  (240)
#define LCD_WIDTH                   (320)

class grove_terminal {
public:
    void begin(bool open = true, uint8_t direction = 1);
    void turn_on();
    void turn_off();
    void foreground(uint16_t color);
    void backround(uint16_t color);
    void print(const char* str);
    void print(const char* str, uint32_t length);
    void print(int32_t value, uint8_t base = 10);
    void print(double value, uint8_t precison = 2);
    void print(char value);
    void println(int32_t value, uint8_t base = 10);
    void println(double value, uint8_t precison = 2);
    void println(char value);
    void println(const char* str);
    void println(const char* str, uint32_t length);
    void printf(const char* fmt, ...);
    void flush();
};
#endif
