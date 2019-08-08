/**
 * The MIT License (MIT)
 *
 * Author: PowerfulCat (x4495@outlook.com)
 *
 * Copyright (C) 2019  Seeed Technology Co.,Ltd.
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

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "py/obj.h"

    typedef struct{
        uint8_t  second;
        uint8_t  minute;
        uint8_t  hour; 
        uint8_t  day_of_week;  // day of week, 1 = Monday
        uint8_t  day_of_month;
        uint8_t  month;
        uint16_t year;
    }rtc_datetime_t;

    typedef struct{
        mp_obj_base_t  base;
        rtc_datetime_t data;
    }datetime_obj_t;

    void common_hal_rtc_construct(void ** get);
    void common_hal_rtc_deinit(void * self);
    void common_hal_rtc_start(void * self);
    void common_hal_rtc_stop(void * self);
    void common_hal_rtc_get_datetime(void * self, rtc_datetime_t * value);
    void common_hal_rtc_set_datetime(void * self, rtc_datetime_t * value);
#ifdef __cplusplus
}
#endif
