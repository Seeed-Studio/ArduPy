/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * Development of the code in this file was sponsored by Seeed Stduio
 *
 * Author: Hontai Liu (hontai.liu@seeed.cc)
 *
 * Copyright (C) 2020  Seeed Technology Co.,Ltd.
 * The MIT License (MIT)
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
#include <stdio.h>

#include "py/nlr.h"
#include "py/runtime.h"
#include "modmachine.h"
#include "mphalport.h"

#include "wrapper_lcd.h"

extern const mp_obj_type_t machine_lcd_type;

m_generic_make(lcd)
{
    abstract_module_t *self = new_abstruct_module(type);
    mp_arg_check_num(n_args, n_kw, 0, 0, false);
    common_hal_lcd_construct(self);
    return self;
}

mp_obj_t lcd_fillScreen(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint16_t color = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_fillScreen(self, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd_fillScreen_obj, 1, lcd_fillScreen);

mp_obj_t lcd_setRotation(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t r = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_setRotation(self, r);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd_setRotation_obj, 1, lcd_setRotation);

mp_obj_t lcd_getRotation(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t rotation = common_hal_lcd_getRotation(self);
    return MP_OBJ_NEW_SMALL_INT(rotation);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd_getRotation_obj, 0, lcd_getRotation);

mp_obj_t lcd_setTextFont(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t font = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_setTextFont(self, font);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_setTextFont_obj, 1, lcd_setTextFont);

mp_obj_t lcd_invertDisplay(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    bool i = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_invertDisplay(self, i);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd_invertDisplay_obj, 1, lcd_invertDisplay);

mp_obj_t lcd_drawPixel(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t color = mp_obj_get_int(args[3]);

    common_hal_lcd_drawPixel(self, x, y, color);

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawPixel_obj, 4, 4, lcd_drawPixel);

mp_obj_t lcd_drawChar(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint16_t uniCode = mp_obj_get_int(args[1]);
    int32_t x = mp_obj_get_int(args[2]);
    int32_t y = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_lcd_drawChar(self, uniCode, x, y, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawChar_obj, 4, 5, lcd_drawChar);

mp_obj_t lcd_drawString(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    int32_t poX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;

    if (n_args == 4)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_lcd_drawString(self, string, poX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawString_obj, 4, 5, lcd_drawString);

mp_obj_t lcd_drawRightString(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    int32_t dX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_lcd_drawRightString(self, string, dX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawRightString_obj, 4, 5, lcd_drawRightString);

mp_obj_t lcd_drawCentreString(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    int32_t dX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_lcd_drawCentreString(self, string, dX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawCentreString_obj, 4, 5, lcd_drawCentreString);

mp_obj_t lcd_fontHeight(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint8_t font = 1;
    if (n_args == 2)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[1]);
    }
    int16_t xReturn = common_hal_lcd_fontHeight(self, font);
    return MP_OBJ_NEW_SMALL_INT(xReturn);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_fontHeight_obj, 2, 3, lcd_fontHeight);

mp_obj_t lcd_textWidth(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    uint8_t font = 1;
    if (n_args == 2)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[1]);
    }
    int16_t xReturn = common_hal_lcd_textWidth(self, string, font);
    return MP_OBJ_NEW_SMALL_INT(xReturn);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_textWidth_obj, 2, 3, lcd_textWidth);

mp_obj_t lcd_drawNumber(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    long long_number = mp_obj_get_int(args[1]);
    int32_t poX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_lcd_drawNumber(self, long_number, poX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawNumber_obj, 4, 5, lcd_drawNumber);

mp_obj_t lcd_drawFloat(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    float floatNumber = mp_obj_get_float(args[1]);
    uint8_t decimal = mp_obj_get_int(args[2]);
    int32_t poX = mp_obj_get_int(args[3]);
    int32_t poY = mp_obj_get_int(args[4]);
    uint8_t font = 1;
    if (n_args == 5)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[5]);
    }
    common_hal_lcd_drawFloat(self, floatNumber, decimal, poX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawFloat_obj, 5, 6, lcd_drawFloat);

mp_obj_t lcd_setTextWrap(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    bool wrapX = mp_obj_get_int(args[1]);
    bool wrapY = false;
    if (n_args == 3)
    {
        wrapY = mp_obj_get_int(args[2]);
    }

    common_hal_lcd_setTextWrap(self, wrapX, wrapY);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_setTextWrap_obj, 2, 3, lcd_setTextWrap);

mp_obj_t lcd_setTextColor(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int16_t fgcolor = mp_obj_get_int(args[1]);
    int16_t bgcolor = 0;
    if (n_args == 3)
    {
        bgcolor = mp_obj_get_int(args[2]);
    }

    common_hal_lcd_setTextColor(self, fgcolor, bgcolor);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_setTextColor_obj, 2, 3, lcd_setTextColor);

mp_obj_t lcd_setTextSize(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t size = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_setTextSize(self, size);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_setTextSize_obj, 1, lcd_setTextSize);

mp_obj_t lcd_setTextDatum(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t datum = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_setTextDatum(self, datum);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_setTextDatum_obj, 1, lcd_setTextDatum);

mp_obj_t lcd_getTextDatum(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t datum = common_hal_lcd_getTextDatum(self);
    return MP_OBJ_NEW_SMALL_INT(datum);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd_getTextDatum_obj, 0, lcd_getTextDatum);

mp_obj_t lcd_setTextPadding(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint16_t x_width = mp_obj_get_int(pos_args[1]);
    common_hal_lcd_setTextPadding(self, x_width);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_setTextPadding_obj, 1, lcd_setTextPadding);

mp_obj_t lcd_drawLine(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t x1 = mp_obj_get_int(args[3]);
    int32_t y1 = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_lcd_drawLine(self, x0, y0, x1, y1, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawLine_obj, 6, 6, lcd_drawLine);

mp_obj_t lcd_drawFastVLine(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t h = mp_obj_get_int(args[3]);
    uint32_t color = mp_obj_get_int(args[4]);
    common_hal_lcd_drawFastVLine(self, x, y, h, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawFastVLine_obj, 5, 5, lcd_drawFastVLine);

mp_obj_t lcd_drawFastHLine(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    uint32_t color = mp_obj_get_int(args[4]);
    common_hal_lcd_drawFastHLine(self, x, y, w, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawFastHLine_obj, 5, 5, lcd_drawFastHLine);

mp_obj_t lcd_fillRect(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    int32_t h = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_lcd_fillRect(self, x, y, w, h, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_fillRect_obj, 6, 6, lcd_fillRect);

mp_obj_t lcd_drawRect(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    int32_t h = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_lcd_drawRect(self, x, y, w, h, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawRect_obj, 6, 6, lcd_drawRect);

mp_obj_t lcd_drawRoundRect(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    int32_t h = mp_obj_get_int(args[4]);
    int32_t r = mp_obj_get_int(args[5]);
    uint32_t color = mp_obj_get_int(args[6]);
    common_hal_lcd_drawRoundRect(self, x, y, w, h, r, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawRoundRect_obj, 7, 7, lcd_drawRoundRect);

mp_obj_t lcd_fillRoundRect(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    int32_t h = mp_obj_get_int(args[4]);
    int32_t r = mp_obj_get_int(args[5]);
    uint32_t color = mp_obj_get_int(args[6]);
    common_hal_lcd_fillRoundRect(self, x, y, w, h, r, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_fillRoundRect_obj, 7, 7, lcd_fillRoundRect);

mp_obj_t lcd_drawCircle(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t r = mp_obj_get_int(args[3]);
    uint32_t color = mp_obj_get_int(args[4]);
    common_hal_lcd_drawCircle(self, x, y, r, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawCircle_obj, 5, 5, lcd_drawCircle);

mp_obj_t lcd_fillCircle(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t r = mp_obj_get_int(args[3]);
    uint32_t color = mp_obj_get_int(args[4]);
    common_hal_lcd_fillCircle(self, x, y, r, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_fillCircle_obj, 5, 5, lcd_fillCircle);

mp_obj_t lcd_drawCircleHelper(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t r = mp_obj_get_int(args[3]);
    uint8_t c = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_lcd_drawCircleHelper(self, x, y, r, c, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawCircleHelper_obj, 6, 6, lcd_drawCircleHelper);

mp_obj_t lcd_fillCircleHelper(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t r = mp_obj_get_int(args[3]);
    uint8_t c = mp_obj_get_int(args[4]);
    int32_t d = mp_obj_get_int(args[3]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_lcd_fillCircleHelper(self, x, y, r, c, d, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_fillCircleHelper_obj, 7, 7, lcd_fillCircleHelper);

mp_obj_t lcd_drawEllipse(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t rx = mp_obj_get_int(args[3]);
    int32_t ry = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_lcd_drawEllipse(self, x0, y0, rx, ry, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawEllipse_obj, 6, 6, lcd_drawEllipse);

mp_obj_t lcd_fillEllipse(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t rx = mp_obj_get_int(args[3]);
    int32_t ry = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_lcd_fillEllipse(self, x0, y0, rx, ry, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_fillEllipse_obj, 6, 6, lcd_fillEllipse);

mp_obj_t lcd_drawTriangle(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t x1 = mp_obj_get_int(args[3]);
    int32_t y1 = mp_obj_get_int(args[4]);
    int32_t x2 = mp_obj_get_int(args[5]);
    int32_t y2 = mp_obj_get_int(args[6]);
    uint32_t color = mp_obj_get_int(args[7]);
    common_hal_lcd_drawTriangle(self, x0, y0, x1, y1, x2, y2, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_drawTriangle_obj, 8, 8, lcd_drawTriangle);

mp_obj_t lcd_fillTriangle(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t x1 = mp_obj_get_int(args[3]);
    int32_t y1 = mp_obj_get_int(args[4]);
    int32_t x2 = mp_obj_get_int(args[5]);
    int32_t y2 = mp_obj_get_int(args[6]);
    uint32_t color = mp_obj_get_int(args[7]);
    common_hal_lcd_fillTriangle(self, x0, y0, x1, y1, x2, y2, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_fillTriangle_obj, 8, 8, lcd_fillTriangle);

mp_obj_t lcd_color565(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint8_t red = mp_obj_get_int(args[1]);
    uint8_t green = mp_obj_get_int(args[2]);
    uint8_t blue = mp_obj_get_int(args[3]);

    uint16_t color = common_hal_lcd_color565(self, red, green, blue);
    return MP_OBJ_NEW_SMALL_INT(color);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_color565_obj, 4, 4, lcd_color565);

mp_obj_t lcd_color8to16(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint8_t color332 = mp_obj_get_int(args[1]);

    uint16_t color = common_hal_lcd_color8to16(self, color332);
    return MP_OBJ_NEW_SMALL_INT(color);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_color8to16_obj, 2, 2, lcd_color8to16);

mp_obj_t lcd_color16to8(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint16_t color565 = mp_obj_get_int(args[1]);

    uint16_t color = common_hal_lcd_color16to8(self, color565);
    return MP_OBJ_NEW_SMALL_INT(color);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_color16to8_obj, 2, 2, lcd_color16to8);

mp_obj_t lcd_setPivot(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int16_t x = mp_obj_get_int(args[1]);
    int16_t y = mp_obj_get_int(args[2]);
    common_hal_lcd_setPivot(self, x, y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_setPivot_obj, 3, 3, lcd_setPivot);

mp_obj_t lcd_setCursor(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int16_t x = mp_obj_get_int(args[1]);
    int16_t y = mp_obj_get_int(args[2]);
    uint8_t font = 1;
    if (n_args == 3)
    {
        font = common_hal_lcd_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[3]);
    }
    common_hal_lcd_setCursor(self, x, y, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_setCursor_obj, 3, 4, lcd_setCursor);

mp_obj_t lcd_getPivotX(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];

    uint16_t value = common_hal_lcd_getPivotX(self);

    return MP_OBJ_NEW_SMALL_INT(value);
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_getPivotX_obj, 1, lcd_getPivotX);

mp_obj_t lcd_getPivotY(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];

    uint16_t value = common_hal_lcd_getPivotY(self);

    return MP_OBJ_NEW_SMALL_INT(value);
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_getPivotY_obj, 1, lcd_getPivotY);

mp_obj_t lcd_getCursorX(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];

    uint16_t value = common_hal_lcd_getCursorX(self);

    return MP_OBJ_NEW_SMALL_INT(value);
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_getCursorX_obj, 1, lcd_getCursorX);

mp_obj_t lcd_getCursorY(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];

    uint16_t value = common_hal_lcd_getCursorY(self);

    return MP_OBJ_NEW_SMALL_INT(value);
}
MP_DEFINE_CONST_FUN_OBJ_KW(lcd_getCursorY_obj, 1, lcd_getCursorY);

mp_obj_t lcd_pushImage(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    int32_t h = mp_obj_get_int(args[4]);
    const uint8_t *data = (uint8_t *)mp_to_ptr(args[5]);
    // uint8_t transparent = 0;
    // bool bpp8 = true;
    // if (n_args == 7)
    // {
    //     transparent = mp_obj_get_int(args[6]);
    // }
    common_hal_lcd_pushImage(self, x0, y0, w, h, data);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lcd_pushImage_obj, 6, 6, lcd_pushImage);

#ifdef MICROPY_PY_LVGL
DEFINE_PTR_OBJ(common_hal_lcd_monitor_flush);
#endif

void lcd_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    abstract_module_t *self = (abstract_module_t *)(self_in);
    if (dest[0] == MP_OBJ_NULL)
    {
        if (attr == MP_QSTR_width)
        {
            dest[0] = mp_obj_new_int(common_hal_lcd_width(self));
            return;
        }
        else if (attr == MP_QSTR_height)
        {
            dest[0] = mp_obj_new_int(common_hal_lcd_height(self));
            return;
        }
    }
    generic_method_lookup(self_in, attr, dest);
}

const mp_rom_map_elem_t lcd_color_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_BLACK), MP_ROM_INT(TFT_BLACK)},
    {MP_ROM_QSTR(MP_QSTR_NAVY), MP_ROM_INT(TFT_NAVY)},
    {MP_ROM_QSTR(MP_QSTR_DARKGREEN), MP_ROM_INT(TFT_DARKGREEN)},
    {MP_ROM_QSTR(MP_QSTR_DARKCYAN), MP_ROM_INT(TFT_DARKCYAN)},
    {MP_ROM_QSTR(MP_QSTR_MAROON), MP_ROM_INT(TFT_MAROON)},
    {MP_ROM_QSTR(MP_QSTR_PURPLE), MP_ROM_INT(TFT_PURPLE)},
    {MP_ROM_QSTR(MP_QSTR_OLIVE), MP_ROM_INT(TFT_OLIVE)},
    {MP_ROM_QSTR(MP_QSTR_LIGHTGREY), MP_ROM_INT(TFT_LIGHTGREY)},
    {MP_ROM_QSTR(MP_QSTR_DARKGREY), MP_ROM_INT(TFT_DARKGREY)},
    {MP_ROM_QSTR(MP_QSTR_BLUE), MP_ROM_INT(TFT_BLUE)},
    {MP_ROM_QSTR(MP_QSTR_GREEN), MP_ROM_INT(TFT_GREEN)},
    {MP_ROM_QSTR(MP_QSTR_CYAN), MP_ROM_INT(TFT_CYAN)},
    {MP_ROM_QSTR(MP_QSTR_RED), MP_ROM_INT(TFT_RED)},
    {MP_ROM_QSTR(MP_QSTR_MAGENTA), MP_ROM_INT(TFT_MAGENTA)},
    {MP_ROM_QSTR(MP_QSTR_YELLOW), MP_ROM_INT(TFT_YELLOW)},
    {MP_ROM_QSTR(MP_QSTR_WHITE), MP_ROM_INT(TFT_WHITE)},
    {MP_ROM_QSTR(MP_QSTR_ORANGE), MP_ROM_INT(TFT_ORANGE)},
    {MP_ROM_QSTR(MP_QSTR_GREENYELLOW), MP_ROM_INT(TFT_GREENYELLOW)},
    {MP_ROM_QSTR(MP_QSTR_BLACK), MP_ROM_INT(TFT_BLACK)},
    {MP_ROM_QSTR(MP_QSTR_PINK), MP_ROM_INT(TFT_PINK)},
};

MP_DEFINE_CONST_DICT(lcd_color_locals_dict, lcd_color_locals_dict_table);

const mp_obj_type_t lcd_color_type = {
    {&mp_type_type},
    .name = MP_QSTR_color,
    .locals_dict = (mp_obj_t)&lcd_color_locals_dict,
};

const mp_rom_map_elem_t lcd_datum_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_TL_DATUM), MP_ROM_INT(TL_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_TC_DATUM), MP_ROM_INT(TC_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_TR_DATUM), MP_ROM_INT(TR_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_ML_DATUM), MP_ROM_INT(ML_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_CL_DATUM), MP_ROM_INT(CL_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_MC_DATUM), MP_ROM_INT(MC_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_CC_DATUM), MP_ROM_INT(CC_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_MR_DATUM), MP_ROM_INT(MR_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_CR_DATUM), MP_ROM_INT(CR_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_BL_DATUM), MP_ROM_INT(BL_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_BC_DATUM), MP_ROM_INT(BC_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_BR_DATUM), MP_ROM_INT(BR_DATUM)},
    {MP_ROM_QSTR(MP_QSTR_L_BASELINE), MP_ROM_INT(L_BASELINE)},
    {MP_ROM_QSTR(MP_QSTR_C_BASELINE), MP_ROM_INT(C_BASELINE)},
    {MP_ROM_QSTR(MP_QSTR_R_BASELINE), MP_ROM_INT(R_BASELINE)},
};

MP_DEFINE_CONST_DICT(lcd_datum_locals_dict, lcd_datum_locals_dict_table);

const mp_obj_type_t lcd_datum_type = {
    {&mp_type_type},
    .name = MP_QSTR_datum,
    .locals_dict = (mp_obj_t)&lcd_datum_locals_dict,
};

const mp_rom_map_elem_t lcd_locals_dict_table[] = {
    // instance methods
    {MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&lcd_deinit_obj)},
    {MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj)},
    {MP_ROM_QSTR(MP_QSTR___exit__), MP_ROM_PTR(&lcd_obj___exit___obj)},
    {MP_ROM_QSTR(MP_QSTR_fillScreen), MP_ROM_PTR(&lcd_fillScreen_obj)},
    {MP_ROM_QSTR(MP_QSTR_setRotation), MP_ROM_PTR(&lcd_setRotation_obj)},
    {MP_ROM_QSTR(MP_QSTR_getRotation), MP_ROM_PTR(&lcd_getRotation_obj)},
    {MP_ROM_QSTR(MP_QSTR_invertDisplay), MP_ROM_PTR(&lcd_invertDisplay_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawRightString), MP_ROM_PTR(&lcd_drawRightString_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawChar), MP_ROM_PTR(&lcd_drawChar_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawString), MP_ROM_PTR(&lcd_drawString_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawCentreString), MP_ROM_PTR(&lcd_drawCentreString_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextFont), MP_ROM_PTR(&lcd_setTextFont_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawPixel), MP_ROM_PTR(&lcd_drawPixel_obj)},
    {MP_ROM_QSTR(MP_QSTR_fontHeight), MP_ROM_PTR(&lcd_fontHeight_obj)},
    {MP_ROM_QSTR(MP_QSTR_textWidth), MP_ROM_PTR(&lcd_textWidth_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawNumber), MP_ROM_PTR(&lcd_drawNumber_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawFloat), MP_ROM_PTR(&lcd_drawFloat_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextColor), MP_ROM_PTR(&lcd_setTextColor_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextSize), MP_ROM_PTR(&lcd_setTextSize_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextWrap), MP_ROM_PTR(&lcd_setTextWrap_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextDatum), MP_ROM_PTR(&lcd_setTextDatum_obj)},
    {MP_ROM_QSTR(MP_QSTR_getTextDatum), MP_ROM_PTR(&lcd_getTextDatum_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextPadding), MP_ROM_PTR(&lcd_setTextPadding_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawLine), MP_ROM_PTR(&lcd_drawLine_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawFastVLine), MP_ROM_PTR(&lcd_drawFastVLine_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawFastHLine), MP_ROM_PTR(&lcd_drawFastHLine_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawRect), MP_ROM_PTR(&lcd_drawRect_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillRect), MP_ROM_PTR(&lcd_fillRect_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawRoundRect), MP_ROM_PTR(&lcd_drawRoundRect_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillRoundRect), MP_ROM_PTR(&lcd_fillRoundRect_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawCircle), MP_ROM_PTR(&lcd_drawCircle_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawCircleHelper), MP_ROM_PTR(&lcd_drawCircleHelper_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillCircle), MP_ROM_PTR(&lcd_fillCircle_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillCircleHelper), MP_ROM_PTR(&lcd_fillCircleHelper_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawEllipse), MP_ROM_PTR(&lcd_drawEllipse_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillEllipse), MP_ROM_PTR(&lcd_fillEllipse_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawTriangle), MP_ROM_PTR(&lcd_drawTriangle_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillTriangle), MP_ROM_PTR(&lcd_fillTriangle_obj)},
    {MP_ROM_QSTR(MP_QSTR_getCursorX), MP_ROM_PTR(&lcd_getCursorX_obj)},
    {MP_ROM_QSTR(MP_QSTR_getCursorY), MP_ROM_PTR(&lcd_getCursorY_obj)},
    {MP_ROM_QSTR(MP_QSTR_getPivotX), MP_ROM_PTR(&lcd_getPivotX_obj)},
    {MP_ROM_QSTR(MP_QSTR_getPivotY), MP_ROM_PTR(&lcd_getPivotY_obj)},
    {MP_ROM_QSTR(MP_QSTR_color16to8), MP_ROM_PTR(&lcd_color16to8_obj)},
    {MP_ROM_QSTR(MP_QSTR_color565), MP_ROM_PTR(&lcd_color565_obj)},
    {MP_ROM_QSTR(MP_QSTR_getPivotX), MP_ROM_PTR(&lcd_color8to16_obj)},
    {MP_ROM_QSTR(MP_QSTR_setCursor), MP_ROM_PTR(&lcd_setCursor_obj)},
    {MP_ROM_QSTR(MP_QSTR_setPivot), MP_ROM_PTR(&lcd_setPivot_obj)},
    {MP_ROM_QSTR(MP_QSTR_pushImage), MP_ROM_PTR(&lcd_pushImage_obj)},
    {MP_ROM_QSTR(MP_QSTR_color), MP_ROM_PTR(&lcd_color_type)},
    {MP_ROM_QSTR(MP_QSTR_datum), MP_ROM_PTR(&lcd_datum_type)},

#ifdef MICROPY_PY_LVGL
    {MP_ROM_QSTR(MP_QSTR_flush), MP_ROM_PTR(&PTR_OBJ(common_hal_lcd_monitor_flush))},
#endif
};

MP_DEFINE_CONST_DICT(lcd_locals_dict, lcd_locals_dict_table);

const mp_obj_type_t machine_lcd_type = {
    {&mp_type_type},
    .name = MP_QSTR_LCD,
    .make_new = lcd_make_new,
    .locals_dict = (mp_obj_t)&lcd_locals_dict,
    .attr = lcd_obj_attr,
};




// TFT_eSprite

extern const mp_obj_type_t machine_eSprite_type;

m_generic_make(eSprite)
{
    abstract_module_t *self = new_abstruct_module(type);
    mp_arg_check_num(n_args, n_kw, 1, 1, false);
    abstract_module_t *tft = (abstract_module_t *)(args[0]);
    // if(mp_obj_is_type(tft, &machine_lcd_type))
    // {

    // }
    common_hal_eSprite_construct(self, tft);
    return self;
}

mp_obj_t eSprite_fillScreen(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint16_t color = mp_obj_get_int(pos_args[1]);
    common_hal_eSprite_fillScreen(self, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_fillScreen_obj, 1, eSprite_fillScreen);

mp_obj_t eSprite_setRotation(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t r = mp_obj_get_int(pos_args[1]);
    common_hal_eSprite_setRotation(self, r);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_setRotation_obj, 1, eSprite_setRotation);

mp_obj_t eSprite_getRotation(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t rotation = common_hal_eSprite_getRotation(self);
    return MP_OBJ_NEW_SMALL_INT(rotation);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_getRotation_obj, 0, eSprite_getRotation);

mp_obj_t eSprite_setTextFont(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t font = mp_obj_get_int(pos_args[1]);
    common_hal_eSprite_setTextFont(self, font);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_setTextFont_obj, 1, eSprite_setTextFont);

mp_obj_t eSprite_invertDisplay(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    bool i = mp_obj_get_int(pos_args[1]);
    common_hal_eSprite_invertDisplay(self, i);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_invertDisplay_obj, 1, eSprite_invertDisplay);

mp_obj_t eSprite_drawPixel(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t color = mp_obj_get_int(args[3]);

    common_hal_eSprite_drawPixel(self, x, y, color);

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawPixel_obj, 4, 4, eSprite_drawPixel);

mp_obj_t eSprite_drawChar(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint16_t uniCode = mp_obj_get_int(args[1]);
    int32_t x = mp_obj_get_int(args[2]);
    int32_t y = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_eSprite_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_eSprite_drawChar(self, uniCode, x, y, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawChar_obj, 4, 5, eSprite_drawChar);

mp_obj_t eSprite_drawString(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    int32_t poX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;

    if (n_args == 4)
    {
        font = common_hal_eSprite_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_eSprite_drawString(self, string, poX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawString_obj, 4, 5, eSprite_drawString);

mp_obj_t eSprite_drawRightString(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    int32_t dX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_eSprite_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_eSprite_drawRightString(self, string, dX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawRightString_obj, 4, 5, eSprite_drawRightString);

mp_obj_t eSprite_drawCentreString(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    int32_t dX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_eSprite_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_eSprite_drawCentreString(self, string, dX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawCentreString_obj, 4, 5, eSprite_drawCentreString);

mp_obj_t eSprite_fontHeight(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint8_t font = 1;
    if (n_args == 2)
    {
        font = common_hal_eSprite_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[1]);
    }
    int16_t xReturn = common_hal_eSprite_fontHeight(self, font);
    return MP_OBJ_NEW_SMALL_INT(xReturn);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_fontHeight_obj, 2, 3, eSprite_fontHeight);

mp_obj_t eSprite_textWidth(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    const char *string = mp_obj_str_get_str(args[1]);
    uint8_t font = 1;
    if (n_args == 2)
    {
        font = common_hal_eSprite_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[1]);
    }
    int16_t xReturn = common_hal_eSprite_textWidth(self, string, font);
    return MP_OBJ_NEW_SMALL_INT(xReturn);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_textWidth_obj, 2, 3, eSprite_textWidth);

mp_obj_t eSprite_drawNumber(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    long long_number = mp_obj_get_int(args[1]);
    int32_t poX = mp_obj_get_int(args[2]);
    int32_t poY = mp_obj_get_int(args[3]);
    uint8_t font = 1;
    if (n_args == 4)
    {
        font = common_hal_eSprite_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[4]);
    }
    common_hal_eSprite_drawNumber(self, long_number, poX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawNumber_obj, 4, 5, eSprite_drawNumber);

mp_obj_t eSprite_drawFloat(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    float floatNumber = mp_obj_get_float(args[1]);
    uint8_t decimal = mp_obj_get_int(args[2]);
    int32_t poX = mp_obj_get_int(args[3]);
    int32_t poY = mp_obj_get_int(args[4]);
    uint8_t font = 1;
    if (n_args == 5)
    {
        font = common_hal_eSprite_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[5]);
    }
    common_hal_eSprite_drawFloat(self, floatNumber, decimal, poX, poY, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawFloat_obj, 5, 6, eSprite_drawFloat);

mp_obj_t eSprite_setTextWrap(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    bool wrapX = mp_obj_get_int(args[1]);
    bool wrapY = false;
    if (n_args == 3)
    {
        wrapY = mp_obj_get_int(args[2]);
    }

    common_hal_eSprite_setTextWrap(self, wrapX, wrapY);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_setTextWrap_obj, 2, 3, eSprite_setTextWrap);

mp_obj_t eSprite_setTextColor(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int16_t fgcolor = mp_obj_get_int(args[1]);
    int16_t bgcolor = 0;
    if (n_args == 3)
    {
        bgcolor = mp_obj_get_int(args[2]);
    }

    common_hal_eSprite_setTextColor(self, fgcolor, bgcolor);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_setTextColor_obj, 2, 3, eSprite_setTextColor);

mp_obj_t eSprite_setTextSize(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t size = mp_obj_get_int(pos_args[1]);
    common_hal_eSprite_setTextSize(self, size);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_setTextSize_obj, 1, eSprite_setTextSize);

mp_obj_t eSprite_setTextDatum(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t datum = mp_obj_get_int(pos_args[1]);
    common_hal_eSprite_setTextDatum(self, datum);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_setTextDatum_obj, 1, eSprite_setTextDatum);

mp_obj_t eSprite_getTextDatum(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint8_t datum = common_hal_eSprite_getTextDatum(self);
    return MP_OBJ_NEW_SMALL_INT(datum);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_getTextDatum_obj, 0, eSprite_getTextDatum);

mp_obj_t eSprite_setTextPadding(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint16_t x_width = mp_obj_get_int(pos_args[1]);
    common_hal_eSprite_setTextPadding(self, x_width);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_setTextPadding_obj, 1, eSprite_setTextPadding);

mp_obj_t eSprite_drawLine(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t x1 = mp_obj_get_int(args[3]);
    int32_t y1 = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_eSprite_drawLine(self, x0, y0, x1, y1, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawLine_obj, 6, 6, eSprite_drawLine);

mp_obj_t eSprite_drawFastVLine(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t h = mp_obj_get_int(args[3]);
    uint32_t color = mp_obj_get_int(args[4]);
    common_hal_eSprite_drawFastVLine(self, x, y, h, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawFastVLine_obj, 5, 5, eSprite_drawFastVLine);

mp_obj_t eSprite_drawFastHLine(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    uint32_t color = mp_obj_get_int(args[4]);
    common_hal_eSprite_drawFastHLine(self, x, y, w, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawFastHLine_obj, 5, 5, eSprite_drawFastHLine);

mp_obj_t eSprite_fillRect(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    int32_t h = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_eSprite_fillRect(self, x, y, w, h, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_fillRect_obj, 6, 6, eSprite_fillRect);

mp_obj_t eSprite_drawRect(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    int32_t h = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_eSprite_drawRect(self, x, y, w, h, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawRect_obj, 6, 6, eSprite_drawRect);

mp_obj_t eSprite_drawRoundRect(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    int32_t h = mp_obj_get_int(args[4]);
    int32_t r = mp_obj_get_int(args[5]);
    uint32_t color = mp_obj_get_int(args[6]);
    common_hal_eSprite_drawRoundRect(self, x, y, w, h, r, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawRoundRect_obj, 7, 7, eSprite_drawRoundRect);

mp_obj_t eSprite_fillRoundRect(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    int32_t h = mp_obj_get_int(args[4]);
    int32_t r = mp_obj_get_int(args[5]);
    uint32_t color = mp_obj_get_int(args[6]);
    common_hal_eSprite_fillRoundRect(self, x, y, w, h, r, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_fillRoundRect_obj, 7, 7, eSprite_fillRoundRect);

mp_obj_t eSprite_drawCircle(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t r = mp_obj_get_int(args[3]);
    uint32_t color = mp_obj_get_int(args[4]);
    common_hal_eSprite_drawCircle(self, x, y, r, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawCircle_obj, 5, 5, eSprite_drawCircle);

mp_obj_t eSprite_fillCircle(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t r = mp_obj_get_int(args[3]);
    uint32_t color = mp_obj_get_int(args[4]);
    common_hal_eSprite_fillCircle(self, x, y, r, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_fillCircle_obj, 5, 5, eSprite_fillCircle);

mp_obj_t eSprite_drawCircleHelper(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t r = mp_obj_get_int(args[3]);
    uint8_t c = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_eSprite_drawCircleHelper(self, x, y, r, c, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawCircleHelper_obj, 6, 6, eSprite_drawCircleHelper);

mp_obj_t eSprite_fillCircleHelper(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t r = mp_obj_get_int(args[3]);
    uint8_t c = mp_obj_get_int(args[4]);
    int32_t d = mp_obj_get_int(args[3]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_eSprite_fillCircleHelper(self, x, y, r, c, d, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_fillCircleHelper_obj, 7, 7, eSprite_fillCircleHelper);

mp_obj_t eSprite_drawEllipse(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t rx = mp_obj_get_int(args[3]);
    int32_t ry = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_eSprite_drawEllipse(self, x0, y0, rx, ry, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawEllipse_obj, 6, 6, eSprite_drawEllipse);

mp_obj_t eSprite_fillEllipse(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t rx = mp_obj_get_int(args[3]);
    int32_t ry = mp_obj_get_int(args[4]);
    uint32_t color = mp_obj_get_int(args[5]);
    common_hal_eSprite_fillEllipse(self, x0, y0, rx, ry, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_fillEllipse_obj, 6, 6, eSprite_fillEllipse);

mp_obj_t eSprite_drawTriangle(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t x1 = mp_obj_get_int(args[3]);
    int32_t y1 = mp_obj_get_int(args[4]);
    int32_t x2 = mp_obj_get_int(args[5]);
    int32_t y2 = mp_obj_get_int(args[6]);
    uint32_t color = mp_obj_get_int(args[7]);
    common_hal_eSprite_drawTriangle(self, x0, y0, x1, y1, x2, y2, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_drawTriangle_obj, 8, 8, eSprite_drawTriangle);

mp_obj_t eSprite_fillTriangle(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t x1 = mp_obj_get_int(args[3]);
    int32_t y1 = mp_obj_get_int(args[4]);
    int32_t x2 = mp_obj_get_int(args[5]);
    int32_t y2 = mp_obj_get_int(args[6]);
    uint32_t color = mp_obj_get_int(args[7]);
    common_hal_eSprite_fillTriangle(self, x0, y0, x1, y1, x2, y2, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_fillTriangle_obj, 8, 8, eSprite_fillTriangle);

mp_obj_t eSprite_color565(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint8_t red = mp_obj_get_int(args[1]);
    uint8_t green = mp_obj_get_int(args[2]);
    uint8_t blue = mp_obj_get_int(args[3]);

    uint16_t color = common_hal_eSprite_color565(self, red, green, blue);
    return MP_OBJ_NEW_SMALL_INT(color);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_color565_obj, 4, 4, eSprite_color565);

mp_obj_t eSprite_color8to16(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint8_t color332 = mp_obj_get_int(args[1]);

    uint16_t color = common_hal_eSprite_color8to16(self, color332);
    return MP_OBJ_NEW_SMALL_INT(color);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_color8to16_obj, 2, 2, eSprite_color8to16);

mp_obj_t eSprite_color16to8(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    uint16_t color565 = mp_obj_get_int(args[1]);

    uint16_t color = common_hal_eSprite_color16to8(self, color565);
    return MP_OBJ_NEW_SMALL_INT(color);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_color16to8_obj, 2, 2, eSprite_color16to8);

mp_obj_t eSprite_setPivot(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int16_t x = mp_obj_get_int(args[1]);
    int16_t y = mp_obj_get_int(args[2]);
    common_hal_eSprite_setPivot(self, x, y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_setPivot_obj, 3, 3, eSprite_setPivot);

mp_obj_t eSprite_setCursor(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int16_t x = mp_obj_get_int(args[1]);
    int16_t y = mp_obj_get_int(args[2]);
    uint8_t font = 1;
    if (n_args == 3)
    {
        font = common_hal_eSprite_getTextFont(self);
    }
    else
    {
        font = mp_obj_get_int(args[3]);
    }
    common_hal_eSprite_setCursor(self, x, y, font);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_setCursor_obj, 3, 4, eSprite_setCursor);

mp_obj_t eSprite_getPivotX(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];

    uint16_t value = common_hal_eSprite_getPivotX(self);

    return MP_OBJ_NEW_SMALL_INT(value);
}
MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_getPivotX_obj, 1, eSprite_getPivotX);

mp_obj_t eSprite_getPivotY(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];

    uint16_t value = common_hal_eSprite_getPivotY(self);

    return MP_OBJ_NEW_SMALL_INT(value);
}
MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_getPivotY_obj, 1, eSprite_getPivotY);

mp_obj_t eSprite_getCursorX(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];

    uint16_t value = common_hal_eSprite_getCursorX(self);

    return MP_OBJ_NEW_SMALL_INT(value);
}
MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_getCursorX_obj, 1, eSprite_getCursorX);

mp_obj_t eSprite_getCursorY(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];

    uint16_t value = common_hal_eSprite_getCursorY(self);

    return MP_OBJ_NEW_SMALL_INT(value);
}
MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_getCursorY_obj, 1, eSprite_getCursorY);

mp_obj_t eSprite_pushImage(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x0 = mp_obj_get_int(args[1]);
    int32_t y0 = mp_obj_get_int(args[2]);
    int32_t w = mp_obj_get_int(args[3]);
    int32_t h = mp_obj_get_int(args[4]);
    const uint8_t *data = (uint8_t *)mp_to_ptr(args[5]);
    // uint8_t transparent = 0;
    // bool bpp8 = true;
    // if (n_args == 7)
    // {
    //     transparent = mp_obj_get_int(args[6]);
    // }
    common_hal_eSprite_pushImage(self, x0, y0, w, h, data);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_pushImage_obj, 6, 6, eSprite_pushImage);

mp_obj_t eSprite_createSprite(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t width = mp_obj_get_int(args[1]);
    int32_t height = mp_obj_get_int(args[2]);
    int32_t frames = 1;
    if (n_args == 4)
    {
        frames = mp_obj_get_int(args[3]);
    }
    common_hal_eSprite_createSprite(self, width, height, frames);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_createSprite_obj, 3, 4, eSprite_createSprite);

mp_obj_t eSprite_pushSprite(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    int32_t x = mp_obj_get_int(args[1]);
    int32_t y = mp_obj_get_int(args[2]);
    int32_t transparent = 1;
    if (n_args == 4)
    {
        transparent = mp_obj_get_int(args[3]);
        common_hal_eSprite_pushSprite2(self, x, y, transparent);
    }else{
        common_hal_eSprite_pushSprite1(self, x, y);
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_pushSprite_obj, 3, 4, eSprite_pushSprite);


mp_obj_t eSprite_deleteSprite(size_t n_args, const mp_obj_t *args)
{
    abstract_module_t *self = (abstract_module_t *)args[0];
    common_hal_eSprite_deletSprite(self);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(eSprite_deleteSprite_obj, 1, 1, eSprite_deleteSprite);


mp_obj_t eSprite_fillSprite(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)
{
    abstract_module_t *self = (abstract_module_t *)pos_args[0];
    uint16_t color = mp_obj_get_int(pos_args[1]);
    common_hal_eSprite_fillSprite(self, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(eSprite_fillSprite_obj, 1, eSprite_fillSprite);

void eSprite_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    abstract_module_t *self = (abstract_module_t *)(self_in);
    if (dest[0] == MP_OBJ_NULL)
    {
        if (attr == MP_QSTR_width)
        {
            dest[0] = mp_obj_new_int(common_hal_eSprite_width(self));
            return;
        }
        else if (attr == MP_QSTR_height)
        {
            dest[0] = mp_obj_new_int(common_hal_eSprite_height(self));
            return;
        }
    }
    generic_method_lookup(self_in, attr, dest);
}

const mp_rom_map_elem_t eSprite_locals_dict_table[] = {
    // instance methods
    {MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&eSprite_deinit_obj)},
    {MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj)},
    {MP_ROM_QSTR(MP_QSTR___exit__), MP_ROM_PTR(&eSprite_obj___exit___obj)},
    {MP_ROM_QSTR(MP_QSTR_fillScreen), MP_ROM_PTR(&eSprite_fillScreen_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillSprite), MP_ROM_PTR(&eSprite_fillSprite_obj)},
    {MP_ROM_QSTR(MP_QSTR_createSprite), MP_ROM_PTR(&eSprite_createSprite_obj)},
    {MP_ROM_QSTR(MP_QSTR_pushSprite), MP_ROM_PTR(&eSprite_pushSprite_obj)},
    {MP_ROM_QSTR(MP_QSTR_deleteSprite), MP_ROM_PTR(&eSprite_deleteSprite_obj)},
    {MP_ROM_QSTR(MP_QSTR_setRotation), MP_ROM_PTR(&eSprite_setRotation_obj)},
    {MP_ROM_QSTR(MP_QSTR_getRotation), MP_ROM_PTR(&eSprite_getRotation_obj)},
    {MP_ROM_QSTR(MP_QSTR_invertDisplay), MP_ROM_PTR(&eSprite_invertDisplay_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawRightString), MP_ROM_PTR(&eSprite_drawRightString_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawChar), MP_ROM_PTR(&eSprite_drawChar_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawString), MP_ROM_PTR(&eSprite_drawString_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawCentreString), MP_ROM_PTR(&eSprite_drawCentreString_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextFont), MP_ROM_PTR(&eSprite_setTextFont_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawPixel), MP_ROM_PTR(&eSprite_drawPixel_obj)},
    {MP_ROM_QSTR(MP_QSTR_fontHeight), MP_ROM_PTR(&eSprite_fontHeight_obj)},
    {MP_ROM_QSTR(MP_QSTR_textWidth), MP_ROM_PTR(&eSprite_textWidth_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawNumber), MP_ROM_PTR(&eSprite_drawNumber_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawFloat), MP_ROM_PTR(&eSprite_drawFloat_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextColor), MP_ROM_PTR(&eSprite_setTextColor_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextSize), MP_ROM_PTR(&eSprite_setTextSize_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextWrap), MP_ROM_PTR(&eSprite_setTextWrap_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextDatum), MP_ROM_PTR(&eSprite_setTextDatum_obj)},
    {MP_ROM_QSTR(MP_QSTR_getTextDatum), MP_ROM_PTR(&eSprite_getTextDatum_obj)},
    {MP_ROM_QSTR(MP_QSTR_setTextPadding), MP_ROM_PTR(&eSprite_setTextPadding_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawLine), MP_ROM_PTR(&eSprite_drawLine_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawFastVLine), MP_ROM_PTR(&eSprite_drawFastVLine_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawFastHLine), MP_ROM_PTR(&eSprite_drawFastHLine_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawRect), MP_ROM_PTR(&eSprite_drawRect_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillRect), MP_ROM_PTR(&eSprite_fillRect_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawRoundRect), MP_ROM_PTR(&eSprite_drawRoundRect_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillRoundRect), MP_ROM_PTR(&eSprite_fillRoundRect_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawCircle), MP_ROM_PTR(&eSprite_drawCircle_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawCircleHelper), MP_ROM_PTR(&eSprite_drawCircleHelper_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillCircle), MP_ROM_PTR(&eSprite_fillCircle_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillCircleHelper), MP_ROM_PTR(&eSprite_fillCircleHelper_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawEllipse), MP_ROM_PTR(&eSprite_drawEllipse_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillEllipse), MP_ROM_PTR(&eSprite_fillEllipse_obj)},
    {MP_ROM_QSTR(MP_QSTR_drawTriangle), MP_ROM_PTR(&eSprite_drawTriangle_obj)},
    {MP_ROM_QSTR(MP_QSTR_fillTriangle), MP_ROM_PTR(&eSprite_fillTriangle_obj)},
    {MP_ROM_QSTR(MP_QSTR_getCursorX), MP_ROM_PTR(&eSprite_getCursorX_obj)},
    {MP_ROM_QSTR(MP_QSTR_getCursorY), MP_ROM_PTR(&eSprite_getCursorY_obj)},
    {MP_ROM_QSTR(MP_QSTR_getPivotX), MP_ROM_PTR(&eSprite_getPivotX_obj)},
    {MP_ROM_QSTR(MP_QSTR_getPivotY), MP_ROM_PTR(&eSprite_getPivotY_obj)},
    {MP_ROM_QSTR(MP_QSTR_color16to8), MP_ROM_PTR(&eSprite_color16to8_obj)},
    {MP_ROM_QSTR(MP_QSTR_color565), MP_ROM_PTR(&eSprite_color565_obj)},
    {MP_ROM_QSTR(MP_QSTR_getPivotX), MP_ROM_PTR(&eSprite_color8to16_obj)},
    {MP_ROM_QSTR(MP_QSTR_setCursor), MP_ROM_PTR(&eSprite_setCursor_obj)},
    {MP_ROM_QSTR(MP_QSTR_setPivot), MP_ROM_PTR(&eSprite_setPivot_obj)},
    {MP_ROM_QSTR(MP_QSTR_pushImage), MP_ROM_PTR(&eSprite_pushImage_obj)},
    {MP_ROM_QSTR(MP_QSTR_color), MP_ROM_PTR(&lcd_color_type)},
    {MP_ROM_QSTR(MP_QSTR_datum), MP_ROM_PTR(&lcd_datum_type)},
};

MP_DEFINE_CONST_DICT(eSprite_locals_dict, eSprite_locals_dict_table);

const mp_obj_type_t machine_eSprite_type = {
    {&mp_type_type},
    .name = MP_QSTR_eSprite,
    .make_new = eSprite_make_new,
    .locals_dict = (mp_obj_t)&eSprite_locals_dict,
    .attr = eSprite_obj_attr,
};

#endif