/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Scott Shawcroft for Adafruit Industries
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

#include "common-hal/grove/GroveRtc.h"
#include "submodule/DS1307.h"
extern "C"{
#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"
}

#define rtc     (*(DS1307 *)self)
void * operator new(size_t, void *);

extern "C"{
    void common_hal_rtc_construct(void ** get){
        DS1307 * self;
        *get = self = new(m_new_obj(DS1307)) DS1307;
        rtc.begin();
    }
    void common_hal_rtc_deinit(void *self){

    }
    void common_hal_rtc_start(void * self){
        rtc.startClock();
    }
    void common_hal_rtc_stop(void * self){
        rtc.stopClock();
    }
    void common_hal_rtc_get_datetime(void * self, rtc_datetime_t * value){
        rtc.getTime();
        value->second = rtc.second;
        value->minute = rtc.minute;
        value->hour = rtc.hour;
        value->day_of_week = rtc.dayOfWeek;
        value->day_of_month = rtc.dayOfMonth;
        value->month = rtc.month;
        value->year = rtc.year;
    }
    void common_hal_rtc_set_datetime(void * self, rtc_datetime_t * value){
        rtc.fillByYMD(value->year, value->month, value->day_of_month);
        rtc.fillByHMS(value->hour, value->minute, value->second);
        rtc.fillDayOfWeek(value->day_of_week);
        rtc.setTime();
    }
}