

/**
 * The MIT License (MIT)
 *
 * Author: Hongtai Liu (lht856@foxmail.com)
 *
 * Copyright (C) 2020  Seeed Technology Co.,Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifdef LCD_SUPPORT

//These enumerate the text plotting alignment (reference datum point)
#define TL_DATUM 0    // Top left (default)
#define TC_DATUM 1    // Top centre
#define TR_DATUM 2    // Top right
#define ML_DATUM 3    // Middle left
#define CL_DATUM 3    // Centre left, same as above
#define MC_DATUM 4    // Middle centre
#define CC_DATUM 4    // Centre centre, same as above
#define MR_DATUM 5    // Middle right
#define CR_DATUM 5    // Centre right, same as above
#define BL_DATUM 6    // Bottom left
#define BC_DATUM 7    // Bottom centre
#define BR_DATUM 8    // Bottom right
#define L_BASELINE 9  // Left character baseline (Line the 'A' character would sit on)
#define C_BASELINE 10 // Centre character baseline
#define R_BASELINE 11 // Right character baseline

// New color definitions use for all my libraries
#define TFT_BLACK 0x0000       /*   0,   0,   0 */
#define TFT_NAVY 0x000F        /*   0,   0, 128 */
#define TFT_DARKGREEN 0x03E0   /*   0, 128,   0 */
#define TFT_DARKCYAN 0x03EF    /*   0, 128, 128 */
#define TFT_MAROON 0x7800      /* 128,   0,   0 */
#define TFT_PURPLE 0x780F      /* 128,   0, 128 */
#define TFT_OLIVE 0x7BE0       /* 128, 128,   0 */
#define TFT_LIGHTGREY 0xC618   /* 192, 192, 192 */
#define TFT_DARKGREY 0x7BEF    /* 128, 128, 128 */
#define TFT_BLUE 0x001F        /*   0,   0, 255 */
#define TFT_GREEN 0x07E0       /*   0, 255,   0 */
#define TFT_CYAN 0x07FF        /*   0, 255, 255 */
#define TFT_RED 0xF800         /* 255,   0,   0 */
#define TFT_MAGENTA 0xF81F     /* 255,   0, 255 */
#define TFT_YELLOW 0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE 0xFFFF       /* 255, 255, 255 */
#define TFT_ORANGE 0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0 /* 180, 255,   0 */
#define TFT_PINK 0xFC9F

#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif
#include "py/objtype.h"
#include "shared-bindings/util.h"
#ifdef MICROPY_PY_LVGL
#include "Seeed_Ardupy_LvGL/lvgl/lvgl.h"
#include "Seeed_Ardupy_LvGL/driver/include/common.h"
    common_hal_lcd_monitor_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
#endif

    void common_hal_lcd_construct(abstract_module_t *self);
    void common_hal_lcd_deinit(abstract_module_t *self);
    void common_hal_lcd_fillScreen(abstract_module_t *self, uint32_t color);
    int16_t common_hal_lcd_width(abstract_module_t *self);
    int16_t common_hal_lcd_height(abstract_module_t *self);
    void common_hal_lcd_setRotation(abstract_module_t *self, uint8_t r);
    void common_hal_lcd_invertDisplay(abstract_module_t *self, bool i);
    void common_hal_lcd_drawPixel(abstract_module_t *self, int32_t x, int32_t y, uint32_t color);
    void common_hal_lcd_setTextFont(abstract_module_t *self, uint8_t font);
    uint8_t common_hal_lcd_getTextFont(abstract_module_t *self);
    void common_hal_lcd_drawChar(abstract_module_t *self, uint16_t uniCode, int32_t x, int32_t y, uint8_t font);
    void common_hal_lcd_drawString(abstract_module_t *self, const char *string, int32_t poX, int32_t poY, uint8_t font);
    void common_hal_lcd_drawCentreString(abstract_module_t *self, const char *string, int32_t dX, int32_t poY, uint8_t font);
    void common_hal_lcd_drawRightString(abstract_module_t *self, const char *string, int32_t dX, int32_t poY, uint8_t font);
    void common_hal_lcd_drawNumber(abstract_module_t *self, long long_num, int32_t poX, int32_t poY, uint8_t font);
    void common_hal_lcd_drawFloat(abstract_module_t *self, float floatNumber, uint8_t decimal, int32_t poX, int32_t poY, uint8_t font);
    int16_t common_hal_lcd_fontHeight(abstract_module_t *self, uint8_t font);
    int16_t common_hal_lcd_textWidth(abstract_module_t *self, const char *string, uint8_t font);
    int16_t common_hal_lcd_fontHeight(abstract_module_t *self, uint8_t font);
    void common_hal_lcd_setTextColor(abstract_module_t *self, uint16_t fgcolor, uint16_t bgcolor);
    void common_hal_lcd_setTextSize(abstract_module_t *self, uint8_t size);
    void common_hal_lcd_setTextWrap(abstract_module_t *self, boolean wrapX, boolean wrapY);
    void common_hal_lcd_setTextDatum(abstract_module_t *self, uint8_t datum);
    void common_hal_lcd_setTextPadding(abstract_module_t *self, uint16_t x_width);
    uint8_t common_hal_lcd_getRotation(abstract_module_t *self);
    uint8_t common_hal_lcd_getTextDatum(abstract_module_t *self);
    void common_hal_lcd_drawLine(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);
    void common_hal_lcd_drawFastVLine(abstract_module_t *self, int32_t x, int32_t y, int32_t h, uint32_t color);
    void common_hal_lcd_drawFastHLine(abstract_module_t *self, int32_t x, int32_t y, int32_t w, uint32_t color);
    void common_hal_lcd_fillRect(abstract_module_t *self, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
    void common_hal_lcd_drawRect(abstract_module_t *self, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
    void common_hal_lcd_drawRoundRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, int32_t radius, uint32_t color);
    void common_hal_lcd_fillRoundRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, int32_t radius, uint32_t color);
    void common_hal_lcd_drawCircle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint32_t color);
    void common_hal_lcd_drawCircleHelper(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint8_t cornername, uint32_t color);
    void common_hal_lcd_fillCircle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint32_t color);
    void common_hal_lcd_fillCircleHelper(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint8_t cornername, int32_t delta, uint32_t color);
    void common_hal_lcd_drawEllipse(abstract_module_t *self, int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color);
    void common_hal_lcd_fillEllipse(abstract_module_t *self, int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color);
    void common_hal_lcd_drawTriangle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);
    void common_hal_lcd_fillTriangle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);
    uint16_t common_hal_lcd_color565(abstract_module_t *self, uint8_t red, uint8_t green, uint8_t blue);
    uint16_t common_hal_lcd_color8to16(abstract_module_t *self, uint8_t color332);
    uint16_t common_hal_lcd_color16to8(abstract_module_t *self, uint16_t color565);
    uint16_t common_hal_lcd_getPivotX(abstract_module_t *self);
    uint16_t common_hal_lcd_getPivotY(abstract_module_t *self);
    uint16_t common_hal_lcd_getCursorX(abstract_module_t *self);
    uint16_t common_hal_lcd_getCursorY(abstract_module_t *self);
    void common_hal_lcd_setPivot(abstract_module_t *self, int16_t x, int16_t y);
    void common_hal_lcd_setCursor(abstract_module_t *self, int16_t x, int16_t y, uint8_t font);
    void common_hal_lcd_pushImage(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint8_t *data);
    void common_hal_lcd_setSwapBytes(abstract_module_t *self, bool swap);
    bool common_hal_lcd_getSwapBytes(abstract_module_t *self);
    void common_hal_lcd_pushRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data);
    void common_hal_lcd_readRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data);

    // function fo eSprite
    void common_hal_eSprite_construct(abstract_module_t *self, abstract_module_t *eTft);
    void common_hal_eSprite_deinit(abstract_module_t *self);
    void common_hal_eSprite_fillScreen(abstract_module_t *self, uint32_t color);
    int16_t common_hal_eSprite_width(abstract_module_t *self);
    int16_t common_hal_eSprite_height(abstract_module_t *self);
    void common_hal_eSprite_setRotation(abstract_module_t *self, uint8_t r);
    void common_hal_eSprite_invertDisplay(abstract_module_t *self, bool i);
    void common_hal_eSprite_drawPixel(abstract_module_t *self, int32_t x, int32_t y, uint32_t color);
    void common_hal_eSprite_setTextFont(abstract_module_t *self, uint8_t font);
    uint8_t common_hal_eSprite_getTextFont(abstract_module_t *self);
    void common_hal_eSprite_drawChar(abstract_module_t *self, uint16_t uniCode, int32_t x, int32_t y, uint8_t font);
    void common_hal_eSprite_drawString(abstract_module_t *self, const char *string, int32_t poX, int32_t poY, uint8_t font);
    void common_hal_eSprite_drawCentreString(abstract_module_t *self, const char *string, int32_t dX, int32_t poY, uint8_t font);
    void common_hal_eSprite_drawRightString(abstract_module_t *self, const char *string, int32_t dX, int32_t poY, uint8_t font);
    void common_hal_eSprite_drawNumber(abstract_module_t *self, long long_num, int32_t poX, int32_t poY, uint8_t font);
    void common_hal_eSprite_drawFloat(abstract_module_t *self, float floatNumber, uint8_t decimal, int32_t poX, int32_t poY, uint8_t font);
    int16_t common_hal_eSprite_fontHeight(abstract_module_t *self, uint8_t font);
    int16_t common_hal_eSprite_textWidth(abstract_module_t *self, const char *string, uint8_t font);
    int16_t common_hal_eSprite_fontHeight(abstract_module_t *self, uint8_t font);
    void common_hal_eSprite_setTextColor(abstract_module_t *self, uint16_t fgcolor, uint16_t bgcolor);
    void common_hal_eSprite_setTextSize(abstract_module_t *self, uint8_t size);
    void common_hal_eSprite_setTextWrap(abstract_module_t *self, boolean wrapX, boolean wrapY);
    void common_hal_eSprite_setTextDatum(abstract_module_t *self, uint8_t datum);
    void common_hal_eSprite_setTextPadding(abstract_module_t *self, uint16_t x_width);
    uint8_t common_hal_eSprite_getRotation(abstract_module_t *self);
    uint8_t common_hal_eSprite_getTextDatum(abstract_module_t *self);
    void common_hal_eSprite_drawLine(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);
    void common_hal_eSprite_drawFastVLine(abstract_module_t *self, int32_t x, int32_t y, int32_t h, uint32_t color);
    void common_hal_eSprite_drawFastHLine(abstract_module_t *self, int32_t x, int32_t y, int32_t w, uint32_t color);
    void common_hal_eSprite_fillRect(abstract_module_t *self, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
    void common_hal_eSprite_drawRect(abstract_module_t *self, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
    void common_hal_eSprite_drawRoundRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, int32_t radius, uint32_t color);
    void common_hal_eSprite_fillRoundRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, int32_t radius, uint32_t color);
    void common_hal_eSprite_drawCircle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint32_t color);
    void common_hal_eSprite_drawCircleHelper(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint8_t cornername, uint32_t color);
    void common_hal_eSprite_fillCircle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint32_t color);
    void common_hal_eSprite_fillCircleHelper(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint8_t cornername, int32_t delta, uint32_t color);
    void common_hal_eSprite_drawEllipse(abstract_module_t *self, int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color);
    void common_hal_eSprite_fillEllipse(abstract_module_t *self, int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color);
    void common_hal_eSprite_drawTriangle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);
    void common_hal_eSprite_fillTriangle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);
    uint16_t common_hal_eSprite_color565(abstract_module_t *self, uint8_t red, uint8_t green, uint8_t blue);
    uint16_t common_hal_eSprite_color8to16(abstract_module_t *self, uint8_t color332);
    uint16_t common_hal_eSprite_color16to8(abstract_module_t *self, uint16_t color565);
    uint16_t common_hal_eSprite_getPivotX(abstract_module_t *self);
    uint16_t common_hal_eSprite_getPivotY(abstract_module_t *self);
    uint16_t common_hal_eSprite_getCursorX(abstract_module_t *self);
    uint16_t common_hal_eSprite_getCursorY(abstract_module_t *self);
    void common_hal_eSprite_setPivot(abstract_module_t *self, int16_t x, int16_t y);
    void common_hal_eSprite_setCursor(abstract_module_t *self, int16_t x, int16_t y, uint8_t font);
    void common_hal_eSprite_pushImage(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data);
    void common_hal_eSprite_setSwapBytes(abstract_module_t *self, bool swap);
    bool common_hal_eSprite_getSwapBytes(abstract_module_t *self);
    void common_hal_eSprite_pushRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data);
    void common_hal_eSprite_readRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data);
    void common_hal_eSprite_createSprite(abstract_module_t *self, int16_t width, int16_t height, uint8_t frames);
    void common_hal_eSprite_deletSprite(abstract_module_t *self);
    void *common_hal_eSprite_frameBuffer(abstract_module_t *self, int8_t f);
    void *common_hal_eSprite_setColorDepth(abstract_module_t *self, int8_t b);
    int8_t common_hal_eSprite_getColorDepth(abstract_module_t *self);
    void common_hal_eSprite_setBitmapColor(abstract_module_t *self, int16_t c, uint16_t b);
    void common_hal_eSprite_fillSprite(abstract_module_t *self, uint32_t color);
    uint16_t common_hal_eSprite_readPixel(abstract_module_t *self, int32_t x0, int32_t y0);
    void common_hal_eSprite_pushSprite1(abstract_module_t *self,int32_t x, int32_t y);
    void common_hal_eSprite_pushSprite2(abstract_module_t *self, int32_t x, int32_t y, uint16_t transparent);

#ifdef __cplusplus
}
#endif

#endif