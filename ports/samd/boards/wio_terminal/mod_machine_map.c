/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * Development of the code in this file was sponsored by Seeed Studio
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
#include <stdio.h>

#include "py/runtime.h"
#include "py/mphal.h"
#ifdef ARDUINO
#include "Arduino.h"
#endif
#include "mphalport.h"

#define ARDUPY_LED_BUILTIN (50ul)
#define ARDUPY_WIO_BUZZER (51ul)
#define ARDUPY_WIO_LIGHT (52ul)
#define ARDUPY_WIO_MIC (53ul)
#define ARDUPY_WIO_IR (54ul)
#define ARDUPY_WIO_KEY_A (55ul)
#define ARDUPY_WIO_KEY_B (56ul)
#define ARDUPY_WIO_KEY_C (57ul)
#define ARDUPY_WIO_5S_UP (58ul)
#define ARDUPY_WIO_5S_LEFT (59ul)
#define ARDUPY_WIO_5S_RIGHT (60ul)
#define ARDUPY_WIO_5S_DOWN (61ul)
#define ARDUPY_WIO_5S_PRESS (62ul)

#define ARDUPY_A0 (13ul)
#define ARDUPY_A1 (15ul)
#define ARDUPY_A2 (16ul)
#define ARDUPY_A3 (18ul)
#define ARDUPY_A4 (22ul)
#define ARDUPY_A5 (32ul)
#define ARDUPY_A6 (33ul)
#define ARDUPY_A7 (36ul)
#define ARDUPY_A8 (37ul)

#define ARDUPY_DAC0 (11ul)
#define ARDUPY_DAC1 (26ul)

const mp_rom_map_elem_t machine_map_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_LED_BUILTIN), MP_ROM_INT(ARDUPY_LED_BUILTIN)},
    {MP_ROM_QSTR(MP_QSTR_WIO_BUZZER), MP_ROM_INT(ARDUPY_WIO_BUZZER)},
    {MP_ROM_QSTR(MP_QSTR_WIO_LIGHT), MP_ROM_INT(ARDUPY_WIO_LIGHT)},
    {MP_ROM_QSTR(MP_QSTR_WIO_MIC), MP_ROM_INT(ARDUPY_WIO_MIC)},
    {MP_ROM_QSTR(MP_QSTR_WIO_IR), MP_ROM_INT(ARDUPY_WIO_IR)},
    {MP_ROM_QSTR(MP_QSTR_WIO_KEY_A), MP_ROM_INT(ARDUPY_WIO_KEY_A)},
    {MP_ROM_QSTR(MP_QSTR_WIO_KEY_B), MP_ROM_INT(ARDUPY_WIO_KEY_B)},
    {MP_ROM_QSTR(MP_QSTR_WIO_KEY_C), MP_ROM_INT(ARDUPY_WIO_KEY_C)},
    {MP_ROM_QSTR(MP_QSTR_WIO_5S_UP), MP_ROM_INT(ARDUPY_WIO_5S_UP)},
    {MP_ROM_QSTR(MP_QSTR_WIO_5S_DOWN), MP_ROM_INT(ARDUPY_WIO_5S_DOWN)},
    {MP_ROM_QSTR(MP_QSTR_WIO_5S_LEFT), MP_ROM_INT(ARDUPY_WIO_5S_LEFT)},
    {MP_ROM_QSTR(MP_QSTR_WIO_5S_RIGHT), MP_ROM_INT(ARDUPY_WIO_5S_RIGHT)},
    {MP_ROM_QSTR(MP_QSTR_WIO_5S_PRESS), MP_ROM_INT(ARDUPY_WIO_5S_PRESS)},
    {MP_ROM_QSTR(MP_QSTR_A0), MP_ROM_INT(ARDUPY_A0)},
    {MP_ROM_QSTR(MP_QSTR_A1), MP_ROM_INT(ARDUPY_A1)},
    {MP_ROM_QSTR(MP_QSTR_A2), MP_ROM_INT(ARDUPY_A2)},
    {MP_ROM_QSTR(MP_QSTR_A3), MP_ROM_INT(ARDUPY_A3)},
    {MP_ROM_QSTR(MP_QSTR_A4), MP_ROM_INT(ARDUPY_A4)},
    {MP_ROM_QSTR(MP_QSTR_A5), MP_ROM_INT(ARDUPY_A5)},
    {MP_ROM_QSTR(MP_QSTR_A6), MP_ROM_INT(ARDUPY_A6)},
    {MP_ROM_QSTR(MP_QSTR_A7), MP_ROM_INT(ARDUPY_A7)},
    {MP_ROM_QSTR(MP_QSTR_A8), MP_ROM_INT(ARDUPY_A8)},
    {MP_ROM_QSTR(MP_QSTR_DAC0), MP_ROM_INT(ARDUPY_DAC0)},
    {MP_ROM_QSTR(MP_QSTR_DAC1), MP_ROM_INT(ARDUPY_DAC1)},
#if WIRE_INTERFACES_COUNT > 0
    {MP_ROM_QSTR(MP_QSTR_WIRE), MP_ROM_INT(0)},
#endif
#if WIRE_INTERFACES_COUNT > 1
    {MP_ROM_QSTR(MP_QSTR_WIRE1), MP_ROM_INT(1)},
#endif
#if WIRE_INTERFACES_COUNT > 2
    {MP_ROM_QSTR(MP_QSTR_WIRE2), MP_ROM_INT(2)},
#endif
#if WIRE_INTERFACES_COUNT > 3
    {MP_ROM_QSTR(MP_QSTR_WIRE3), MP_ROM_INT(3)},
#endif
#if WIRE_INTERFACES_COUNT > 4
    {MP_ROM_QSTR(MP_QSTR_WIRE4), MP_ROM_INT(4)},
#endif
#if WIRE_INTERFACES_COUNT > 5
    {MP_ROM_QSTR(MP_QSTR_WIRE5), MP_ROM_INT(5)},
#endif
#if SPI_INTERFACES_COUNT > 0
    {MP_ROM_QSTR(MP_QSTR_SPI), MP_ROM_INT(0)},
#endif
#if SPI_INTERFACES_COUNT > 1
    {MP_ROM_QSTR(MP_QSTR_SPI1), MP_ROM_INT(1)},
#endif
#if SPI_INTERFACES_COUNT > 2
    {MP_ROM_QSTR(MP_QSTR_SPI2), MP_ROM_INT(2)},
#endif
#if SPI_INTERFACES_COUNT > 3
    {MP_ROM_QSTR(MP_QSTR_SPI3), MP_ROM_INT(3)},
#endif
#if SPI_INTERFACES_COUNT > 4
    {MP_ROM_QSTR(MP_QSTR_SPI4), MP_ROM_INT(4)},
#endif
#if SPI_INTERFACES_COUNT > 5
    {MP_ROM_QSTR(MP_QSTR_SPI5), MP_ROM_INT(5)},
#endif
#if UART_INTERFACES_COUNT > 0
    {MP_ROM_QSTR(MP_QSTR_UART1), MP_ROM_INT(1)},
#endif
#if UART_INTERFACES_COUNT > 1
    {MP_ROM_QSTR(MP_QSTR_UART2), MP_ROM_INT(2)},
#endif
#if UART_INTERFACES_COUNT > 2
    {MP_ROM_QSTR(MP_QSTR_UART3), MP_ROM_INT(3)},
#endif
#if UART_INTERFACES_COUNT > 3
    {MP_ROM_QSTR(MP_QSTR_UART4), MP_ROM_INT(4)},
#endif
#if UART_INTERFACES_COUNT > 4
    {MP_ROM_QSTR(MP_QSTR_UART5), MP_ROM_INT(5)},
#endif
};

MP_DEFINE_CONST_DICT(machine_map_locals_dict, machine_map_dict_table);

const mp_obj_type_t machine_map_type = {
    {&mp_type_type},
    .name = MP_QSTR_Map,
    .locals_dict = (mp_obj_t)&machine_map_locals_dict,
};
