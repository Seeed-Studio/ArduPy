/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Scott Shawcroft
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

#ifndef MICROPY_INCLUDED_ATMEL_SAMD_COMMON_HAL_MICROCONTROLLER_PIN_H
#define MICROPY_INCLUDED_ATMEL_SAMD_COMMON_HAL_MICROCONTROLLER_PIN_H

#include <assert.h>
#include <stdint.h>
#include "py/obj.h"

#ifdef MICROPY_HW_NEOPIXEL
extern bool neopixel_in_use;
#endif
#ifdef MICROPY_HW_APA102_MOSI
extern bool apa102_sck_in_use;
extern bool apa102_mosi_in_use;
#endif
typedef struct {
    mp_obj_base_t base;
    // These could be squeezed to fewer bits if more fields are needed.
    uint8_t number;      // port << 5 | pin number in port (0-31): 6 bits needed
    bool has_extint:1;
    uint8_t extint_channel:7;
    uint8_t adc_channel; // 0 is no ADC, ADC channel from 1 to 8:
                         // 4 bits needed here; 5 bits used in periph registers
} mcu_pin_obj_t;


void reset_all_pins(void);
// reset_pin_number takes the pin number instead of the pointer so that objects don't
// need to store a full pointer.
void reset_pin_number(uint8_t pin_number);
void never_reset_pin_number(uint8_t pin_number);
void claim_pin(const mcu_pin_obj_t* pin);
bool pin_number_is_free(uint8_t pin_number);

#define PORT_BITS 84

#define NO_PIN PORT_BITS

#if defined(ARDUINO_ARCH_SAMD)
#define BOARD_I2C 1
#define BOARD_SPI 1
#define BOARD_UART 1


#endif

extern const mcu_pin_obj_t pin_PA02;
extern const mcu_pin_obj_t pin_PB08;
extern const mcu_pin_obj_t pin_PB09;
extern const mcu_pin_obj_t pin_PA04;
extern const mcu_pin_obj_t pin_PA05;
extern const mcu_pin_obj_t pin_PB02;
extern const mcu_pin_obj_t pin_PA11;
extern const mcu_pin_obj_t pin_PA11;
extern const mcu_pin_obj_t pin_PA10;
extern const mcu_pin_obj_t pin_PA10;
extern const mcu_pin_obj_t pin_PA14;
extern const mcu_pin_obj_t pin_PA09;
extern const mcu_pin_obj_t pin_PA08;
extern const mcu_pin_obj_t pin_PA15;
extern const mcu_pin_obj_t pin_PA20;
extern const mcu_pin_obj_t pin_PA21;
extern const mcu_pin_obj_t pin_PA06;
extern const mcu_pin_obj_t pin_PA07;
extern const mcu_pin_obj_t pin_PA18;
extern const mcu_pin_obj_t pin_PA16;
extern const mcu_pin_obj_t pin_PA19;
extern const mcu_pin_obj_t pin_PA17;
extern const mcu_pin_obj_t pin_XXX;
extern const mcu_pin_obj_t pin_PA22;
extern const mcu_pin_obj_t pin_PA23;
extern const mcu_pin_obj_t pin_PB11;
extern const mcu_pin_obj_t pin_PB10;
extern const mcu_pin_obj_t pin_PA12;



#endif // MICROPY_INCLUDED_ATMEL_SAMD_COMMON_HAL_MICROCONTROLLER_PIN_H
