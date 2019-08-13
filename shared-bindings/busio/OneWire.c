/*
 * This file is part of the Micro Python project, http://micropython.org/
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

#include <stdint.h>


#include "py/runtime.h"
#include "py/runtime0.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"

void common_hal_busio_onewire_construct(abstract_module_t * module, uint32_t pin);
bool common_hal_busio_onewire_deinited(abstract_module_t * self);
void common_hal_busio_onewire_deinit(abstract_module_t * self);
bool common_hal_busio_onewire_read_bit(abstract_module_t * self);
void common_hal_busio_onewire_write_bit(abstract_module_t * self, bool bit);
result_t common_hal_busio_onewire_reset(abstract_module_t * self);

extern const mp_obj_type_t busio_onewire_type;
//| .. currentmodule:: busio
//|
//| :class:`OneWire` -- Lowest-level of the Maxim OneWire protocol
//| =================================================================
//|
//| :class:`~busio.OneWire` implements the timing-sensitive foundation of the Maxim
//| (formerly Dallas Semi) OneWire protocol.
//|
//| Protocol definition is here: https://www.maximintegrated.com/en/app-notes/index.mvp/id/126
//|
//| .. class:: OneWire(pin)
//|
//|   Create a OneWire object associated with the given pin. The object
//|   implements the lowest level timing-sensitive bits of the protocol.
//|
//|   :param ~microcontroller.Pin pin: Pin connected to the OneWire bus
//|
//|   Read a short series of pulses::
//|
//|     import busio
//|     import board
//|
//|     onewire = busio.OneWire(board.D7)
//|     onewire.reset()
//|     onewire.write_bit(True)
//|     onewire.write_bit(False)
//|     print(onewire.read_bit())
//|

m_generic_make(busio_onewire){
    enum { ARG_ctrl };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_pin, MP_ARG_REQUIRED | MP_ARG_OBJ },
    };

    abstract_module_t * self = new_abstruct_module(&busio_onewire_type);
    mcu_pin_obj_t     * pin;
    mp_arg_val_t        vals[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, args, MP_ARRAY_SIZE(allowed_args), allowed_args, vals);
    pin = m_get_pin(ARG_ctrl);
    assert_pin(pin, false);
    assert_pin_free(pin);
    common_hal_busio_onewire_construct(self, pin->number);
    return self;
}

//|   .. method:: reset()
//|
//|     Reset the OneWire bus and read presence
//|
//|     :returns: False when at least one device is present
//|     :rtype: bool
//|
STATIC mp_obj_t busio_onewire_obj_reset(mp_obj_t self_in) {
    abstract_module_t * self = (abstract_module_t *)self_in;
    raise_error_if_deinited(common_hal_busio_onewire_deinited(self));
    return mp_obj_new_bool(
        common_hal_busio_onewire_reset(self) == SUCCESS ? 
        false : true
    );
}
MP_DEFINE_CONST_FUN_OBJ_1(busio_onewire_reset_obj, busio_onewire_obj_reset);

//|   .. method:: read_bit()
//|
//|     Read in a bit
//|
//|     :returns: bit state read
//|     :rtype: bool
//|
STATIC mp_obj_t busio_onewire_obj_read_bit(mp_obj_t self_in) {
    abstract_module_t * self = (abstract_module_t *)self_in;
    raise_error_if_deinited(common_hal_busio_onewire_deinited(self));
    return mp_obj_new_bool(common_hal_busio_onewire_read_bit(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(busio_onewire_read_bit_obj, busio_onewire_obj_read_bit);

//|   .. method:: write_bit(value)
//|
//|     Write out a bit based on value.
//|
STATIC mp_obj_t busio_onewire_obj_write_bit(mp_obj_t self_in, mp_obj_t bool_obj) {
    abstract_module_t * self = (abstract_module_t *)self_in;
    raise_error_if_deinited(common_hal_busio_onewire_deinited(self));
    common_hal_busio_onewire_write_bit(self, mp_obj_is_true(bool_obj));
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(busio_onewire_write_bit_obj, busio_onewire_obj_write_bit);

STATIC const mp_rom_map_elem_t busio_onewire_locals_dict_table[] = {
    // Methods
    { MP_ROM_QSTR(MP_QSTR_deinit),    MP_ROM_PTR(&busio_onewire_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),  MP_ROM_PTR(&busio_onewire_obj___exit___obj) },
    { MP_ROM_QSTR(MP_QSTR_reset),     MP_ROM_PTR(&busio_onewire_reset_obj) },
    { MP_ROM_QSTR(MP_QSTR_read_bit),  MP_ROM_PTR(&busio_onewire_read_bit_obj) },
    { MP_ROM_QSTR(MP_QSTR_write_bit), MP_ROM_PTR(&busio_onewire_write_bit_obj) },
};
STATIC MP_DEFINE_CONST_DICT(busio_onewire_locals_dict, busio_onewire_locals_dict_table);

const mp_obj_type_t busio_onewire_type = {
    { &mp_type_type },
    .name = MP_QSTR_OneWire,
    .make_new = busio_onewire_make_new,
    .locals_dict = (mp_obj_dict_t*)&busio_onewire_locals_dict,
};
