// /**
//  * The MIT License (MIT)
//  *
//  * Author: LynnL4 (lht856@foxmail.com)
//  *
//  * Copyright (C) 2020  Seeed Technology Co.,Ltd.
//  *
//  * Permission is hereby granted, free of charge, to any person obtaining a copy
//  * of this software and associated documentation files (the "Software"), to deal
//  * in the Software without restriction, including without limitation the rights
//  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  * copies of the Software, and to permit persons to whom the Software is
//  * furnished to do so, subject to the following conditions:
//  *
//  * The above copyright notice and this permission notice shall be included in
//  * all copies or substantial portions of the Software.
//  *
//  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  * THE SOFTWARE.
//  */
#ifdef LCD_SUPPORT
#include <Arduino.h>
#define private public
#define protected public
#include <TFT_eSPI.h>
#include "wrapper_lcd.h"
#include "py/gc.h"

#ifdef MICROPY_PY_LVGL
#include "Seeed_Ardupy_LvGL/lvgl/lvgl.h"
#endif

extern "C"
{
#include "py/objtype.h"
#include "shared-bindings/util.h"
}

#define tft_eSprite (*(TFT_eSprite *)self->module)

#define tft (*(TFT_eSPI *)self->module)
void *operator new(size_t, void *);

#ifdef MICROPY_PY_LVGL
STATIC TFT_eSPI *lv_tft = NULL;
#endif

extern "C"
{
    void common_hal_lcd_construct(abstract_module_t *self)
    {
        self->module = new (m_new_obj(TFT_eSPI)) TFT_eSPI;
#ifdef MICROPY_PY_LVGL
        lv_tft = (TFT_eSPI *)self->module;
#endif
        tft.init();
        tft.setRotation(3);
    }

    void common_hal_lcd_deinit(abstract_module_t *self)
    {
#ifdef MICROPY_PY_LVGL
        lv_tft = NULL;
#endif
        tft.~TFT_eSPI();
    }

    void common_hal_lcd_fillScreen(abstract_module_t *self, uint32_t color)
    {
        tft.fillScreen(color);
    }

    int16_t common_hal_lcd_width(abstract_module_t *self)
    {
        return tft.width();
    }

    int16_t common_hal_lcd_height(abstract_module_t *self)
    {
        return tft.height();
    }

    void common_hal_lcd_setRotation(abstract_module_t *self, uint8_t r)
    {
        tft.setRotation(r);
    }

    uint8_t common_hal_lcd_getRotation(abstract_module_t *self)
    {
        return tft.getRotation();
    }

    void common_hal_lcd_invertDisplay(abstract_module_t *self, bool i)
    {
        tft.invertDisplay(i);
    }

    void common_hal_lcd_drawPixel(abstract_module_t *self, int32_t x, int32_t y, uint32_t color)
    {
        tft.drawPixel(x, y, color);
    }

    void common_hal_lcd_setTextFont(abstract_module_t *self, uint8_t font)
    {
        tft.setTextFont(font);
    }

    uint8_t common_hal_lcd_getTextFont(abstract_module_t *self)
    {
        return tft.textfont;
    }

    void common_hal_lcd_drawChar(abstract_module_t *self, uint16_t uniCode, int32_t x, int32_t y, uint8_t font)
    {
        tft.drawChar(uniCode, x, y, font);
    }

    void common_hal_lcd_drawString(abstract_module_t *self, const char *string, int32_t poX, int32_t poY, uint8_t font)
    {
        tft.drawString(string, poX, poY, font);
    }

    void common_hal_lcd_drawNumber(abstract_module_t *self, long long_num, int32_t poX, int32_t poY, uint8_t font)
    {
        tft.drawNumber(long_num, poX, poY, font);
    }

    void common_hal_lcd_drawFloat(abstract_module_t *self, float floatNumber, uint8_t decimal, int32_t poX, int32_t poY, uint8_t font)
    {
        tft.drawFloat(floatNumber, decimal, poX, poY, font);
    }

    void common_hal_lcd_drawCentreString(abstract_module_t *self, const char *string, int32_t dX, int32_t poY, uint8_t font)
    {
        tft.drawCentreString(string, dX, poY, font);
    }

    void common_hal_lcd_drawRightString(abstract_module_t *self, const char *string, int32_t dX, int32_t poY, uint8_t font)
    {
        tft.drawRightString(string, dX, poY, font);
    }

    int16_t common_hal_lcd_fontHeight(abstract_module_t *self, uint8_t font)
    {
        return tft.fontHeight(font);
    }

    int16_t common_hal_lcd_textWidth(abstract_module_t *self, const char *string, uint8_t font)
    {
        return tft.textWidth(string, font);
    }

    void common_hal_lcd_setTextColor(abstract_module_t *self, uint16_t fgcolor, uint16_t bgcolor)
    {
        tft.setTextColor(fgcolor, bgcolor);
    }

    void common_hal_lcd_setTextSize(abstract_module_t *self, uint8_t size)
    {
        tft.setTextSize(size);
    }

    void common_hal_lcd_setTextWrap(abstract_module_t *self, boolean wrapX, boolean wrapY)
    {
        tft.setTextWrap(wrapX, wrapY);
    }

    void common_hal_lcd_setTextDatum(abstract_module_t *self, uint8_t datum)
    {
        tft.setTextDatum(datum);
    }
    uint8_t common_hal_lcd_getTextDatum(abstract_module_t *self)
    {
        return tft.getTextDatum();
    }
    void common_hal_lcd_setTextPadding(abstract_module_t *self, uint16_t x_width)
    {
        tft.setTextPadding(x_width);
    }

    void common_hal_lcd_drawLine(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
    {
        tft.drawLine(x0, y0, x1, y1, color);
    }
    void common_hal_lcd_drawFastVLine(abstract_module_t *self, int32_t x, int32_t y, int32_t h, uint32_t color)
    {
        tft.drawFastVLine(x, y, h, color);
    }

    void common_hal_lcd_drawFastHLine(abstract_module_t *self, int32_t x, int32_t y, int32_t w, uint32_t color)
    {
        tft.drawFastHLine(x, y, w, color);
    }

    void common_hal_lcd_fillRect(abstract_module_t *self, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
    {
        tft.fillRect(x, y, w, h, color);
    }

    void common_hal_lcd_drawRect(abstract_module_t *self, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
    {
        tft.drawRect(x, y, w, h, color);
    }
    void common_hal_lcd_drawRoundRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, int32_t radius, uint32_t color)
    {
        tft.drawRoundRect(x0, y0, w, h, radius, color);
    }
    void common_hal_lcd_fillRoundRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, int32_t radius, uint32_t color)
    {
        tft.fillRoundRect(x0, y0, w, h, radius, color);
    }
    void common_hal_lcd_drawCircle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint32_t color)
    {
        tft.drawCircle(x0, y0, r, color);
    }
    void common_hal_lcd_drawCircleHelper(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint8_t cornername, uint32_t color)
    {
        tft.drawCircleHelper(x0, y0, r, cornername, color);
    }
    void common_hal_lcd_fillCircle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint32_t color)
    {
        tft.fillCircle(x0, y0, r, color);
    }
    void common_hal_lcd_fillCircleHelper(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint8_t cornername, int32_t delta, uint32_t color)
    {
        tft.fillCircleHelper(x0, y0, r, cornername, delta, color);
    }
    void common_hal_lcd_drawEllipse(abstract_module_t *self, int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color)
    {
        tft.drawEllipse(x0, y0, rx, ry, color);
    }
    void common_hal_lcd_fillEllipse(abstract_module_t *self, int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color)
    {
        tft.fillEllipse(x0, y0, rx, ry, color);
    }
    void common_hal_lcd_drawTriangle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color)
    {
        tft.drawTriangle(x0, y0, x1, y1, x2, y2, color);
    }
    void common_hal_lcd_fillTriangle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color)
    {
        tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
    }
    uint16_t common_hal_lcd_color565(abstract_module_t *self, uint8_t red, uint8_t green, uint8_t blue)
    {
        return tft.color565(red, green, blue);
    }
    uint16_t common_hal_lcd_color8to16(abstract_module_t *self, uint8_t color332)
    {
        return tft.color8to16(color332);
    }
    uint16_t common_hal_lcd_color16to8(abstract_module_t *self, uint16_t color565)
    {
        return tft.color16to8(color565);
    }
    uint16_t common_hal_lcd_getPivotX(abstract_module_t *self)
    {
        return tft.getPivotX();
    }
    uint16_t common_hal_lcd_getPivotY(abstract_module_t *self)
    {
        return tft.getPivotY();
    }
    uint16_t common_hal_lcd_getCursorX(abstract_module_t *self)
    {
        return tft.getCursorX();
    }
    uint16_t common_hal_lcd_getCursorY(abstract_module_t *self)
    {
        return tft.getCursorY();
    }
    void common_hal_lcd_setPivot(abstract_module_t *self, int16_t x, int16_t y)
    {
        return tft.setPivot(x, y);
    }
    void common_hal_lcd_setCursor(abstract_module_t *self, int16_t x, int16_t y, uint8_t font)
    {
        return tft.setCursor(x, y, font);
    }
    void common_hal_lcd_pushImage(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint8_t *data)
    {
        tft.pushImage(x0, y0, w, h, (uint8_t *)data);
    }
    void common_hal_lcd_setSwapBytes(abstract_module_t *self, bool swap)
    {
        tft.setSwapBytes(swap);
    }
    bool common_hal_lcd_getSwapBytes(abstract_module_t *self)
    {
        return tft.getSwapBytes();
    }
    void common_hal_lcd_pushRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data)
    {
        tft.pushRect(x0, y0, w, h, data);
    }
    void common_hal_lcd_readRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data)
    {
        tft.readRect(x0, y0, w, h, data);
    }

    //function of tft_sSprite

    void common_hal_eSprite_construct(abstract_module_t *self, abstract_module_t *eTft)
    {

        TFT_eSPI * _tft = (TFT_eSPI *)eTft->module;
        self->module = new (m_new_obj(TFT_eSprite)) TFT_eSprite(_tft);
        tft_eSprite.setColorDepth(8);
    }

    void common_hal_eSprite_deinit(abstract_module_t *self)
    {
        common_hal_eSprite_deletSprite(self);
        tft_eSprite.~TFT_eSprite();
    }

    void common_hal_eSprite_createSprite(abstract_module_t *self, int16_t width, int16_t height, uint8_t frames)
    {
        uint8_t* p = (uint8_t*)m_malloc(width*height+1*sizeof(uint8_t));
        if(p == NULL){
            printf("error gc alloc");
        }
        tft_eSprite.createSprite(width, height, p, frames);
    
    }

    void common_hal_eSprite_deletSprite(abstract_module_t *self)
    {
        m_free(tft_eSprite._img8_1);
        tft_eSprite._created = false;
        tft_eSprite.deleteSprite();
    }

    void* common_hal_eSprite_frameBuffer(abstract_module_t *self, int8_t f)
    {
        return tft_eSprite.frameBuffer(f);
    }

    void* common_hal_eSprite_setColorDepth(abstract_module_t *self, int8_t b)
    {
        return tft_eSprite.setColorDepth(b);
    }

    int8_t   common_hal_eSprite_getColorDepth(abstract_module_t *self)
    {
        return tft_eSprite.getColorDepth();
    }

    void common_hal_eSprite_setBitmapColor(abstract_module_t *self, int16_t c, uint16_t b)
    {
        return tft_eSprite.setBitmapColor(c, b);
    }

    void common_hal_eSprite_fillSprite(abstract_module_t *self, uint32_t color)
    {
        tft_eSprite.fillSprite(color);
    }

    uint16_t common_hal_eSprite_readPixel(abstract_module_t *self,int32_t x0, int32_t y0)
    {
        return tft_eSprite.readPixel(x0, y0);
    }

    void common_hal_eSprite_pushSprite1(abstract_module_t *self,int32_t x, int32_t y)
    {
        return tft_eSprite.pushSprite(x, y);
    }

    void common_hal_eSprite_pushSprite2(abstract_module_t *self,int32_t x, int32_t y, uint16_t transparent)
    {
        return tft_eSprite.pushSprite(x, y, transparent);
    }

    void common_hal_eSprite_fillScreen(abstract_module_t *self, uint32_t color)
    {
        tft_eSprite.fillScreen(color);
    }

    int16_t common_hal_eSprite_width(abstract_module_t *self)
    {
        return tft_eSprite.width();
    }

    int16_t common_hal_eSprite_height(abstract_module_t *self)
    {
        return tft_eSprite.height();
    }

    void common_hal_eSprite_setRotation(abstract_module_t *self, uint8_t r)
    {
        tft_eSprite.setRotation(r);
    }

    uint8_t common_hal_eSprite_getRotation(abstract_module_t *self)
    {
        return tft_eSprite.getRotation();
    }

    void common_hal_eSprite_invertDisplay(abstract_module_t *self, bool i)
    {
        tft_eSprite.invertDisplay(i);
    }

    void common_hal_eSprite_drawPixel(abstract_module_t *self, int32_t x, int32_t y, uint32_t color)
    {
        tft_eSprite.drawPixel(x, y, color);
    }

    void common_hal_eSprite_setTextFont(abstract_module_t *self, uint8_t font)
    {
        tft_eSprite.setTextFont(font);
    }

    uint8_t common_hal_eSprite_getTextFont(abstract_module_t *self)
    {
        return tft_eSprite.textfont;
    }

    void common_hal_eSprite_drawChar(abstract_module_t *self, uint16_t uniCode, int32_t x, int32_t y, uint8_t font)
    {
        tft_eSprite.drawChar(uniCode, x, y, font);
    }

    void common_hal_eSprite_drawString(abstract_module_t *self, const char *string, int32_t poX, int32_t poY, uint8_t font)
    {
        tft_eSprite.drawString(string, poX, poY, font);
    }

    void common_hal_eSprite_drawNumber(abstract_module_t *self, long long_num, int32_t poX, int32_t poY, uint8_t font)
    {
        tft_eSprite.drawNumber(long_num, poX, poY, font);
    }

    void common_hal_eSprite_drawFloat(abstract_module_t *self, float floatNumber, uint8_t decimal, int32_t poX, int32_t poY, uint8_t font)
    {
        tft_eSprite.drawFloat(floatNumber, decimal, poX, poY, font);
    }

    void common_hal_eSprite_drawCentreString(abstract_module_t *self, const char *string, int32_t dX, int32_t poY, uint8_t font)
    {
        tft_eSprite.drawCentreString(string, dX, poY, font);
    }

    void common_hal_eSprite_drawRightString(abstract_module_t *self, const char *string, int32_t dX, int32_t poY, uint8_t font)
    {
        tft_eSprite.drawRightString(string, dX, poY, font);
    }

    int16_t common_hal_eSprite_fontHeight(abstract_module_t *self, uint8_t font)
    {
        return tft_eSprite.fontHeight(font);
    }

    int16_t common_hal_eSprite_textWidth(abstract_module_t *self, const char *string, uint8_t font)
    {
        return tft_eSprite.textWidth(string, font);
    }

    void common_hal_eSprite_setTextColor(abstract_module_t *self, uint16_t fgcolor, uint16_t bgcolor)
    {
        tft_eSprite.setTextColor(fgcolor, bgcolor);
    }

    void common_hal_eSprite_setTextSize(abstract_module_t *self, uint8_t size)
    {
        tft_eSprite.setTextSize(size);
    }

    void common_hal_eSprite_setTextWrap(abstract_module_t *self, boolean wrapX, boolean wrapY)
    {
        tft_eSprite.setTextWrap(wrapX, wrapY);
    }

    void common_hal_eSprite_setTextDatum(abstract_module_t *self, uint8_t datum)
    {
        tft_eSprite.setTextDatum(datum);
    }
    uint8_t common_hal_eSprite_getTextDatum(abstract_module_t *self)
    {
        return tft_eSprite.getTextDatum();
    }
    void common_hal_eSprite_setTextPadding(abstract_module_t *self, uint16_t x_width)
    {
        tft_eSprite.setTextPadding(x_width);
    }

    void common_hal_eSprite_drawLine(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
    {
        tft_eSprite.drawLine(x0, y0, x1, y1, color);
    }
    void common_hal_eSprite_drawFastVLine(abstract_module_t *self, int32_t x, int32_t y, int32_t h, uint32_t color)
    {
        tft_eSprite.drawFastVLine(x, y, h, color);
    }

    void common_hal_eSprite_drawFastHLine(abstract_module_t *self, int32_t x, int32_t y, int32_t w, uint32_t color)
    {
        tft_eSprite.drawFastHLine(x, y, w, color);
    }

    void common_hal_eSprite_fillRect(abstract_module_t *self, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
    {
        tft_eSprite.fillRect(x, y, w, h, color);
    }

    void common_hal_eSprite_drawRect(abstract_module_t *self, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
    {
        tft_eSprite.drawRect(x, y, w, h, color);
    }
    void common_hal_eSprite_drawRoundRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, int32_t radius, uint32_t color)
    {
        tft_eSprite.drawRoundRect(x0, y0, w, h, radius, color);
    }
    void common_hal_eSprite_fillRoundRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, int32_t radius, uint32_t color)
    {
        tft_eSprite.fillRoundRect(x0, y0, w, h, radius, color);
    }
    void common_hal_eSprite_drawCircle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint32_t color)
    {
        tft_eSprite.drawCircle(x0, y0, r, color);
    }
    void common_hal_eSprite_drawCircleHelper(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint8_t cornername, uint32_t color)
    {
        tft_eSprite.drawCircleHelper(x0, y0, r, cornername, color);
    }
    void common_hal_eSprite_fillCircle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint32_t color)
    {
        tft_eSprite.fillCircle(x0, y0, r, color);
    }
    void common_hal_eSprite_fillCircleHelper(abstract_module_t *self, int32_t x0, int32_t y0, int32_t r, uint8_t cornername, int32_t delta, uint32_t color)
    {
        tft_eSprite.fillCircleHelper(x0, y0, r, cornername, delta, color);
    }
    void common_hal_eSprite_drawEllipse(abstract_module_t *self, int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color)
    {
        tft_eSprite.drawEllipse(x0, y0, rx, ry, color);
    }
    void common_hal_eSprite_fillEllipse(abstract_module_t *self, int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color)
    {
        tft_eSprite.fillEllipse(x0, y0, rx, ry, color);
    }
    void common_hal_eSprite_drawTriangle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color)
    {
        tft_eSprite.drawTriangle(x0, y0, x1, y1, x2, y2, color);
    }
    void common_hal_eSprite_fillTriangle(abstract_module_t *self, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color)
    {
        tft_eSprite.fillTriangle(x0, y0, x1, y1, x2, y2, color);
    }
    uint16_t common_hal_eSprite_color565(abstract_module_t *self, uint8_t red, uint8_t green, uint8_t blue)
    {
        return tft_eSprite.color565(red, green, blue);
    }
    uint16_t common_hal_eSprite_color8to16(abstract_module_t *self, uint8_t color332)
    {
        return tft_eSprite.color8to16(color332);
    }
    uint16_t common_hal_eSprite_color16to8(abstract_module_t *self, uint16_t color565)
    {
        return tft_eSprite.color16to8(color565);
    }
    uint16_t common_hal_eSprite_getPivotX(abstract_module_t *self)
    {
        return tft_eSprite.getPivotX();
    }
    uint16_t common_hal_eSprite_getPivotY(abstract_module_t *self)
    {
        return tft_eSprite.getPivotY();
    }
    uint16_t common_hal_eSprite_getCursorX(abstract_module_t *self)
    {
        return tft_eSprite.getCursorX();
    }
    uint16_t common_hal_eSprite_getCursorY(abstract_module_t *self)
    {
        return tft_eSprite.getCursorY();
    }
    void common_hal_eSprite_setPivot(abstract_module_t *self, int16_t x, int16_t y)
    {
        return tft_eSprite.setPivot(x, y);
    }
    void common_hal_eSprite_setCursor(abstract_module_t *self, int16_t x, int16_t y, uint8_t font)
    {
        return tft_eSprite.setCursor(x, y, font);
    }
    void common_hal_eSprite_pushImage(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data)
    {
        tft_eSprite.pushImage(x0, y0, w, h, (uint16_t *)data);
    }
    void common_hal_eSprite_setSwapBytes(abstract_module_t *self, bool swap)
    {
        tft_eSprite.setSwapBytes(swap);
    }
    bool common_hal_eSprite_getSwapBytes(abstract_module_t *self)
    {
        return tft_eSprite.getSwapBytes();
    }
    void common_hal_eSprite_pushRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data)
    {
        tft_eSprite.pushRect(x0, y0, w, h, data);
    }
    void common_hal_eSprite_readRect(abstract_module_t *self, int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data)
    {
        tft_eSprite.readRect(x0, y0, w, h, data);
    }

#ifdef MICROPY_PY_LVGL
    void common_hal_lcd_monitor_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
    {
        uint16_t c;
        /*Return if the area is out the screen or the tft is not active*/
        if (area->x2 < 0 || area->y2 < 0 || area->x1 > lv_tft->width() - 1 || area->y1 > lv_tft->height() - 1 || lv_tft == NULL)
        {
            lv_disp_flush_ready(disp_drv);
            return;
        }

        lv_tft->startWrite();                                                                            /* Start new TFT transaction */
        lv_tft->setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1)); /* set the working window */
        for (int y = area->y1; y <= area->y2; y++)
        {
            for (int x = area->x1; x <= area->x2; x++)
            {
                c = color_p->full;
                lv_tft->writeColor(c, 1);
                color_p++;
            }
        }
        lv_tft->endWrite();            /* terminate TFT transaction */
        lv_disp_flush_ready(disp_drv); /* tell lvgl that flushing is done */
    }
#endif
}
#endif