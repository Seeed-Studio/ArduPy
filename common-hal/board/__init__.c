/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
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

#include <string.h>

#include "py/runtime.h"
#include "py/mphal.h"
#include "common-hal/microcontroller/Pin.h"

// typedef struct {
//     mp_obj_base_t base;
//     // These could be squeezed to fewer bits if more fields are needed.
//     uint8_t number;      // port << 5 | pin number in port (0-31): 6 bits needed
//     bool has_extint:1;
//     uint8_t extint_channel:7;
//     uint8_t adc_channel; // 0 is no ADC, ADC channel from 1 to 8:
//                          // 4 bits needed here; 5 bits used in periph registers
// } mcu_pin_obj_t;

#define EXTINT_CHANNEL(channel) \
    .has_extint = true, \
    .extint_channel = channel,

#define NO_EXTINT \
    .has_extint = false,

#define ADC_INPUT(input) \
    .adc_channel = input

#define NO_ADC \
    .adc_channel = 0xff

#define PIN_PREFIX_VALUES { &mcu_pin_type },
// This macro is used to simplify pin definition in boards/<board>/pins.c
#define PIN(p_number, p_name, p_extint, p_adc) \
const mcu_pin_obj_t pin_## p_name = { \
    PIN_PREFIX_VALUES \
    .number = p_number, \
    p_extint \
    p_adc \
}

extern const mp_obj_type_t mcu_pin_type;

//PIN(PA03, EXTINT_CHANNEL(3), ADC_INPUT(1));

// Pins in datasheet order.
// NOTE(tannewt): TC wave out 0 is commented out because the first channel is
// used to vary the 16 bit timer's frequency.
#if defined(PIN_PA00) && !defined(IGNORE_PIN_PA00)
PIN(46, PA00, EXTINT_CHANNEL(0), NO_ADC);
#endif
#if defined(PIN_PA01) && !defined(IGNORE_PIN_PA01)
PIN(47, PA01, EXTINT_CHANNEL(1), NO_ADC);
#endif
#if defined(PIN_PA02) && !defined(IGNORE_PIN_PA02)
// Touch is not allowed on A0 (PA02) on Circuit Playground Express.
PIN(14, PA02, EXTINT_CHANNEL(2), ADC_INPUT(0));
#endif
#if defined(PIN_PA03) && !defined(IGNORE_PIN_PA03)
PIN(42, PA03, EXTINT_CHANNEL(3), ADC_INPUT(1));
#endif
#if defined(PIN_PB04) && !defined(IGNORE_PIN_PB04)
PIN(47, PB04, EXTINT_CHANNEL(4), ADC_INPUT(12));
#endif
#if defined(PIN_PB05) && !defined(IGNORE_PIN_PB05)
PIN(48, PB05, EXTINT_CHANNEL(5), ADC_INPUT(13));
#endif
#if defined(PIN_PB06) && !defined(IGNORE_PIN_PB06)
PIN(49, PB06, EXTINT_CHANNEL(6), ADC_INPUT(14));
#endif
#if defined(PIN_PB07) && !defined(IGNORE_PIN_PB07)
PIN(50, PB07, EXTINT_CHANNEL(7), ADC_INPUT(15));
#endif
#if defined(PIN_PB08) && !defined(IGNORE_PIN_PB08)
PIN(15, PB08, EXTINT_CHANNEL(8), ADC_INPUT(2));
#endif
#if defined(PIN_PB09) && !defined(IGNORE_PIN_PB09)
PIN(16, PB09, EXTINT_CHANNEL(9), ADC_INPUT(3));
#endif
#if defined(PIN_PA04) && !defined(IGNORE_PIN_PA04)
PIN(17, PA04, EXTINT_CHANNEL(4), ADC_INPUT(4));
#endif
#if defined(PIN_PA05) && !defined(IGNORE_PIN_PA05)
PIN(18, PA05, EXTINT_CHANNEL(5), ADC_INPUT(5));
#endif
#if defined(PIN_PA06) && !defined(IGNORE_PIN_PA06)
PIN(40, PA06, EXTINT_CHANNEL(6), ADC_INPUT(6));
#endif
#if defined(PIN_PA07) && !defined(IGNORE_PIN_PA07)
PIN(41, PA07, EXTINT_CHANNEL(7), ADC_INPUT(7));
#endif
#if defined(PIN_PA08) && !defined(IGNORE_PIN_PA08)
PIN(4,  PA08, NO_EXTINT, ADC_INPUT(16));
#endif
#if defined(PIN_PA09) && !defined(IGNORE_PIN_PA09)
PIN(3, PA09, EXTINT_CHANNEL(9), ADC_INPUT(17));
#endif
#if defined(PIN_PA10) && !defined(IGNORE_PIN_PA10)
PIN(1, PA10, EXTINT_CHANNEL(10), ADC_INPUT(18));
#endif
#if defined(PIN_PA11) && !defined(IGNORE_PIN_PA11)
PIN(0, PA11, EXTINT_CHANNEL(11), ADC_INPUT(19));
#endif
#if defined(PIN_PB10) && !defined(IGNORE_PIN_PB10)
PIN(23, PB10, EXTINT_CHANNEL(10), NO_ADC);
#endif
#if defined(PIN_PB11) && !defined(IGNORE_PIN_PB11)
PIN(24, PB11, EXTINT_CHANNEL(11), NO_ADC);
#endif
#if defined(PIN_PB12) && !defined(IGNORE_PIN_PB12)
PIN(51, PB12, EXTINT_CHANNEL(12), NO_ADC);
#endif
#if defined(PIN_PB13) && !defined(IGNORE_PIN_PB13)
PIN(52, PB13, EXTINT_CHANNEL(13), NO_ADC);
#endif
#if defined(PIN_PB14) && !defined(IGNORE_PIN_PB14)
PIN(53, PB14, EXTINT_CHANNEL(14), NO_ADC);
#endif

// Second page.
#if defined(PIN_PB15) && !defined(IGNORE_PIN_PB15)
PIN(54, PB15, EXTINT_CHANNEL(15), NO_ADC);
#endif
#if defined(PIN_PA12) && !defined(IGNORE_PIN_PA12)
PIN(22, PA12, EXTINT_CHANNEL(12), NO_ADC);
#endif
#if defined(PIN_PA13) && !defined(IGNORE_PIN_PA13)
PIN(38, PA13, EXTINT_CHANNEL(13), NO_ADC);
#endif
#if defined(PIN_PA14) && !defined(IGNORE_PIN_PA14)
PIN(2, PA14, EXTINT_CHANNEL(14), NO_ADC);
#endif
#if defined(PIN_PA15) && !defined(IGNORE_PIN_PA15)
PIN(5, PA15, EXTINT_CHANNEL(15), NO_ADC);
#endif
#if defined(PIN_PA16) && !defined(IGNORE_PIN_PA16)
PIN(11, PA16, EXTINT_CHANNEL(0), NO_ADC);
#endif

#if defined(PIN_PA17) && !defined(IGNORE_PIN_PA17)
PIN(13, PA17, EXTINT_CHANNEL(1), NO_ADC);
#endif
const mcu_pin_obj_t pin_XXX = {
    { &mcu_pin_type },
    .number = 13,
    .has_extint = false, 
    .extint_channel = 9,
    .adc_channel = 0xff
};

#if defined(PIN_PA18) && !defined(IGNORE_PIN_PA18)
PIN(10, PA18, EXTINT_CHANNEL(2), NO_ADC);
#endif
#if defined(PIN_PA19) && !defined(IGNORE_PIN_PA19)
PIN(12, PA19, EXTINT_CHANNEL(3), NO_ADC);
#endif
#if defined(PIN_PB16) && !defined(IGNORE_PIN_PB16)
PIN(55, PB16, EXTINT_CHANNEL(0), NO_ADC);
#endif
#if defined(PIN_PB17) && !defined(IGNORE_PIN_PB17)
PIN(56, PB17, EXTINT_CHANNEL(1), NO_ADC);
#endif
#if defined(PIN_PA20) && !defined(IGNORE_PIN_PA20)
PIN(57, PA20, EXTINT_CHANNEL(4), NO_ADC);
#endif
#if defined(PIN_PA21) && !defined(IGNORE_PIN_PA21)
PIN(39, PA21, EXTINT_CHANNEL(5), NO_ADC);
#endif
#if defined(PIN_PA22) && !defined(IGNORE_PIN_PA22)
PIN(58, PA22, EXTINT_CHANNEL(6), NO_ADC);
#endif
#if defined(PIN_PA23) && !defined(IGNORE_PIN_PA23)
PIN(21, PA23, EXTINT_CHANNEL(7), NO_ADC);
#endif
#if defined(PIN_PA24) && !defined(IGNORE_PIN_PA24)
PIN(28, PA24,EXTINT_CHANNEL(12), NO_ADC);
#endif

#if defined(PIN_PA25) && !defined(IGNORE_PIN_PA25)
PIN(29, PA25, EXTINT_CHANNEL(13), NO_ADC);
#endif
#if defined(PIN_PB22) && !defined(IGNORE_PIN_PB22)
PIN(30, PB22, EXTINT_CHANNEL(6), NO_ADC);
#endif
#if defined(PIN_PB23) && !defined(IGNORE_PIN_PB23)
PIN(31, PB23, EXTINT_CHANNEL(7), NO_ADC);
#endif
#if defined(PIN_PA27) && !defined(IGNORE_PIN_PA27)
PIN(26, PA27, EXTINT_CHANNEL(15), NO_ADC);
#endif
#if defined(PIN_PA28) && !defined(IGNORE_PIN_PA28)
PIN(27, PA28, EXTINT_CHANNEL(8), NO_ADC);
#endif
#if defined(PIN_PA30) && !defined(IGNORE_PIN_PA30)
PIN(44, PA30, EXTINT_CHANNEL(10), NO_ADC);
#endif
#if defined(PIN_PA31) && !defined(IGNORE_PIN_PA31)
PIN(45, PA31, EXTINT_CHANNEL(11), NO_ADC);
#endif
#if defined(PIN_PB30) && !defined(IGNORE_PIN_PB30)
PIN(59, PB30, EXTINT_CHANNEL(14), NO_ADC);
#endif
#if defined(PIN_PB31) && !defined(IGNORE_PIN_PB31)
PIN(60, PB31, EXTINT_CHANNEL(15), NO_ADC);
#endif
#if defined(PIN_PB00) && !defined(IGNORE_PIN_PB00)
PIN(61, PB00, EXTINT_CHANNEL(0), ADC_INPUT(8));
#endif
#if defined(PIN_PB01) && !defined(IGNORE_PIN_PB01)
PIN(62, PB01, EXTINT_CHANNEL(1), ADC_INPUT(9));
#endif
#if defined(PIN_PB02) && !defined(IGNORE_PIN_PB02)
PIN(19, PB02, EXTINT_CHANNEL(2), ADC_INPUT(10));
#endif
#if defined(PIN_PB03) && !defined(IGNORE_PIN_PB03)
PIN(25, PB03, EXTINT_CHANNEL(3), ADC_INPUT(11));
#endif
