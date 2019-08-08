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

#include "shared-bindings/busio/I2C.h"
#include "shared-bindings/busio/SPI.h"
#include "shared-bindings/busio/UART.h"



#include "py/obj.h"
#include "py/runtime.h"

#include "shared-bindings/board/__init__.h"
#include "common-hal/microcontroller/Pin.h"
//| :mod:`board` --- Board specific pin names
//| ========================================================
//|
//| .. module:: board
//|   :synopsis: Board specific pin names
//|   :platform: SAMD21
//|
//| Common container for board base pin names. These will vary from board to
//| board so don't expect portability when using this module.
//|
//| .. warning:: The board module varies by board. The APIs documented here may or may not be
//|              available on a specific board.

//| .. method:: I2C()
//|
//|   Returns the `busio.I2C` object for the board designated SDA and SCL pins. It is a singleton.
//|

#if BOARD_I2C
mp_obj_t board_i2c(void) {
    busio_i2c_obj_t *self = m_new_obj(busio_i2c_obj_t);
    self->base.type = &busio_i2c_type;

    common_hal_busio_i2c_construct(self, DEFAULT_I2C_BUS_SCL, DEFAULT_I2C_BUS_SDA, 400000, 0); 
    MP_STATE_VM(shared_i2c_bus) = MP_OBJ_FROM_PTR(self);
    return MP_STATE_VM(shared_i2c_bus);
}
#else
mp_obj_t board_i2c(void) {
    mp_raise_NotImplementedError_varg("No default %q bus", MP_QSTR_I2C);
    return NULL;
}
#endif
MP_DEFINE_CONST_FUN_OBJ_0(board_i2c_obj, board_i2c);


//| .. method:: SPI()
//|
//|   Returns the `busio.SPI` object for the board designated SCK, MOSI and MISO pins. It is a
//|   singleton.
//|
#if BOARD_SPI

// Statically allocate the SPI object so it can live past the end of the heap and into the next VM.
// That way it can be used by built-in FourWire displays and be accessible through board.SPI().
STATIC busio_spi_obj_t spi_obj;
STATIC mp_obj_t spi_singleton = NULL;


mp_obj_t board_spi(void) {
    if (spi_singleton != NULL) {
        return spi_singleton;
    }
    busio_spi_obj_t *self = &spi_obj;
    self->base.type = &busio_spi_type;

    const mcu_pin_obj_t* clock = MP_OBJ_TO_PTR(DEFAULT_SPI_BUS_SCK);
    const mcu_pin_obj_t* mosi = MP_OBJ_TO_PTR(DEFAULT_SPI_BUS_MOSI);
    const mcu_pin_obj_t* miso = MP_OBJ_TO_PTR(DEFAULT_SPI_BUS_MISO);
    common_hal_busio_spi_construct(self, clock, mosi, miso);
    spi_singleton = (mp_obj_t)self;
    return spi_singleton;
}
#else
mp_obj_t board_spi(void) {
    mp_raise_NotImplementedError_varg("No default %q bus", MP_QSTR_SPI);
    return NULL;
}
#endif
MP_DEFINE_CONST_FUN_OBJ_0(board_spi_obj, board_spi);

//| .. method:: UART()
//|
//|   Returns the `busio.UART` object for the board designated TX and RX pins. It is a singleton.
//|
#if BOARD_UART
mp_obj_t board_uart(void) {
    busio_uart_obj_t *self = m_new_obj(busio_uart_obj_t);
    self->base.type = &busio_uart_type;

    const mcu_pin_obj_t* rx = MP_OBJ_TO_PTR(DEFAULT_UART_BUS_RX);
    const mcu_pin_obj_t* tx = MP_OBJ_TO_PTR(DEFAULT_UART_BUS_TX);

    common_hal_busio_uart_construct(self, tx, rx, 9600, 8, PARITY_NONE, 1, 1000, 64);
    MP_STATE_VM(shared_uart_bus) = MP_OBJ_FROM_PTR(self);
    return MP_STATE_VM(shared_uart_bus);
}
#else
mp_obj_t board_uart(void) {
    mp_raise_NotImplementedError_varg("No default %q bus", MP_QSTR_SPI);
    return NULL;
}
#endif
MP_DEFINE_CONST_FUN_OBJ_0(board_uart_obj, board_uart);

const mp_obj_module_t board_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&board_module_globals,
};

STATIC const mp_rom_map_elem_t board_global_dict_table[] = { 
    { MP_ROM_QSTR(MP_QSTR_D0),   MP_ROM_PTR(&pin_D0) },
    { MP_ROM_QSTR(MP_QSTR_D1),   MP_ROM_PTR(&pin_D1) },
    { MP_ROM_QSTR(MP_QSTR_D2),   MP_ROM_PTR(&pin_D2) },
    { MP_ROM_QSTR(MP_QSTR_D3),   MP_ROM_PTR(&pin_D3) },
    { MP_ROM_QSTR(MP_QSTR_D4),   MP_ROM_PTR(&pin_D4) },
    { MP_ROM_QSTR(MP_QSTR_D5),   MP_ROM_PTR(&pin_D5) },
    { MP_ROM_QSTR(MP_QSTR_D6),   MP_ROM_PTR(&pin_D6) },
    { MP_ROM_QSTR(MP_QSTR_D7),   MP_ROM_PTR(&pin_D7) },
    { MP_ROM_QSTR(MP_QSTR_D8),   MP_ROM_PTR(&pin_D8) },
    { MP_ROM_QSTR(MP_QSTR_D9),   MP_ROM_PTR(&pin_D9) },
    { MP_ROM_QSTR(MP_QSTR_D10),  MP_ROM_PTR(&pin_D10) },
    { MP_ROM_QSTR(MP_QSTR_D11),  MP_ROM_PTR(&pin_D11) },
    { MP_ROM_QSTR(MP_QSTR_D12),  MP_ROM_PTR(&pin_D12) },
    { MP_ROM_QSTR(MP_QSTR_D13),  MP_ROM_PTR(&pin_D13) },
    { MP_ROM_QSTR(MP_QSTR_A0),   MP_ROM_PTR(&pin_A0) },
    { MP_ROM_QSTR(MP_QSTR_A1),   MP_ROM_PTR(&pin_A1) },
    { MP_ROM_QSTR(MP_QSTR_A2),   MP_ROM_PTR(&pin_A2) },
    { MP_ROM_QSTR(MP_QSTR_A3),   MP_ROM_PTR(&pin_A3) },
    { MP_ROM_QSTR(MP_QSTR_A4),   MP_ROM_PTR(&pin_A4) },
    { MP_ROM_QSTR(MP_QSTR_A5),   MP_ROM_PTR(&pin_A5) },
    { MP_ROM_QSTR(MP_QSTR_RX),   MP_ROM_PTR(&pin_RX) },
    { MP_ROM_QSTR(MP_QSTR_TX),   MP_ROM_PTR(&pin_TX) },
    { MP_ROM_QSTR(MP_QSTR_SDA),  MP_ROM_PTR(&pin_SDA) },
    { MP_ROM_QSTR(MP_QSTR_SCL),  MP_ROM_PTR(&pin_SCL) },
    { MP_ROM_QSTR(MP_QSTR_SCK),  MP_ROM_PTR(&pin_SCK) },
    { MP_ROM_QSTR(MP_QSTR_MOSI), MP_ROM_PTR(&pin_MOSI) },
    { MP_ROM_QSTR(MP_QSTR_MISO), MP_ROM_PTR(&pin_MISO) },
    { MP_ROM_QSTR(MP_QSTR_I2C),  MP_ROM_PTR(&board_i2c_obj) },
    { MP_ROM_QSTR(MP_QSTR_SPI),  MP_ROM_PTR(&board_spi_obj) },
    { MP_ROM_QSTR(MP_QSTR_UART), MP_ROM_PTR(&board_uart_obj) },
};
MP_DEFINE_CONST_DICT(board_module_globals, board_global_dict_table);             

void reset_board_busses(void) {
#if BOARD_I2C
    MP_STATE_VM(shared_i2c_bus) = NULL;
#endif
#if BOARD_SPI
    bool display_using_spi = false;
    #ifdef CIRCUITPY_DISPLAYIO
    for (uint8_t i = 0; i < CIRCUITPY_DISPLAY_LIMIT; i++) {
        if (displays[i].fourwire_bus.bus == spi_singleton) {
            display_using_spi = true;
            break;
        }
    }
    #endif
    if (!display_using_spi) {
        spi_singleton = NULL;
    }
#endif
#if BOARD_UART
    MP_STATE_VM(shared_uart_bus) = NULL;
#endif
}
