#include"grove_terminal.h"
#include"stdio.h"
#include"string.h"
#include"TFT_eSPI.h"
#define LCD_PRINT_LINE_HEIGHT       (12)
#define LCD_PRINT_LINE_WIDTH        (8)
#define LCD_PRINT_ROW_COUNT         (LCD_HEIGHT / LCD_PRINT_LINE_HEIGHT)
#define LCD_PRINT_COLUMN_COUNT      (LCD_WIDTH / LCD_PRINT_LINE_WIDTH)

namespace {
    bool       is_full_row;
    char       buffer[LCD_PRINT_ROW_COUNT * (1 + LCD_PRINT_COLUMN_COUNT)];
    uint8_t    column_count[LCD_PRINT_ROW_COUNT];
    uint16_t   lcd_print_row_count;
    uint16_t   lcd_print_column_count;
    uint16_t   current_row;
    uint16_t   current_column;
    uint16_t   fore = TFT_GREEN;
    uint16_t   back = TFT_BLACK;
    TFT_eSPI   tft;
    static char* get_row(uint32_t index) {
        return buffer + (index * lcd_print_column_count);
    }
    static char* break_row() {
        current_column = 0;
        current_row++;
        if (current_row == lcd_print_row_count) {
            is_full_row = true;
            current_row = 0;
        }
        auto row = get_row(current_row);
        row[0] = '\0';
        return row;
    }
}

void grove_terminal::begin(bool open, uint8_t direction) {
    tft.init();
    tft.setRotation(direction);
    tft.setTextSize(1);
    tft.fillScreen(back);
    tft.setTextColor(fore, back);
    current_row = 0;
    current_column = 0;
    if (open) {
        turn_on();
    }
    if (direction & 1) {
        lcd_print_row_count = LCD_PRINT_ROW_COUNT;
        lcd_print_column_count = LCD_PRINT_COLUMN_COUNT;
    }
    else {
        lcd_print_row_count = (LCD_WIDTH / LCD_PRINT_LINE_HEIGHT);
        lcd_print_column_count = (LCD_HEIGHT / LCD_PRINT_LINE_WIDTH);
    }
}
void grove_terminal::turn_on(){
    pinMode(LCD_BACKLIGHT, OUTPUT);
    digitalWrite(LCD_BACKLIGHT, HIGH);
}
void grove_terminal::turn_off() {
    pinMode(LCD_BACKLIGHT, OUTPUT);
    digitalWrite(LCD_BACKLIGHT, LOW);
}
void grove_terminal::foreground(uint16_t color) {
    fore = color;
    tft.setTextColor(fore, back);
    flush();
}
void grove_terminal::backround(uint16_t color) {
    back = color;
    tft.fillScreen(back);
    tft.setTextColor(fore, back);
    flush();
}

void grove_terminal::print(const char* str){
    print(str, strlen(str));
}
void grove_terminal::print(const char* str, uint32_t length){
    char * row = current_column == lcd_print_column_count ? break_row() : get_row(current_row);
    for (uint32_t i = 0; str[i] != '\0' && i < length; i++) {
        switch (str[i]) {
        case '\t':
        case '\v':
        case '\r':
            continue;
        case '\n':
            row[current_column] = '\0';
            current_column = lcd_print_column_count;
            break;
        default:
            row[current_column++] = str[i];
            break;
        }
        if (current_column == lcd_print_column_count) {
            if (str[i] != '\n') {
                row[lcd_print_column_count] = '\0';
            }
            if (str[i + 1] != '\0' || str[i] == '\n') {
                row = break_row();
            }
        }
    }
    row[current_column] = '\0';  
}
void grove_terminal::print(int32_t value, uint8_t base) {
    char buf[33];
    itoa(value, buf, base);
    print(buf);
}
void grove_terminal::print(double value, uint8_t precison) {
    char fmt[10];
    char buf[33];
    sprintf(fmt, "%%.%uf", precison);
    sprintf(buf, fmt, value);
    print(buf);
}
void grove_terminal::print(char value) {
    char buf[] = { value, '\0' };
    print(buf);
}
void grove_terminal::println(int32_t value, uint8_t base) {
    print(value, base);
    print("\n");
}
void grove_terminal::println(double value, uint8_t precison) {
    print(value, precison);
    print("\n");
}
void grove_terminal::println(char value) {
    char buf[] = { value, '\n', '\0' };
    print(buf);
}
void grove_terminal::println(const char* str) {
    print(str);
    print("\n");
}
void grove_terminal::println(const char* str, uint32_t length) {
    print(str, length);
    print("\n");
}
void grove_terminal::printf(const char* fmt, ...) {
    char buf[128];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    print(buf);
    va_end(ap);
}
void grove_terminal::flush() {
    uint32_t i = 0;
    uint32_t index = 0;
    uint32_t height = 0;
    uint32_t row_count = current_row + 1;
    if (is_full_row) {
        index = current_row + 1;
        row_count = lcd_print_row_count;
    }
    while (i < row_count){
        if (index == lcd_print_row_count) {
            index = 0;
        }
        auto start = get_row(index), p = start;
        auto width = 0;
        for (; p[0]; p++, width += LCD_PRINT_LINE_WIDTH) {
            tft.drawChar(p[0], width, height, 1);
        }
        for (uint32_t ws = p - start; ws < column_count[i]; ws++, width += LCD_PRINT_LINE_WIDTH) {
            tft.drawChar(' ', width, height, 1);
        }
        column_count[i] = p - start;
        height += LCD_PRINT_LINE_HEIGHT;
        index += 1;
        i += 1;
    }
}