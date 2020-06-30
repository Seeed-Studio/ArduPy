/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Development of the code in this file was sponsored by Seeed Studio
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

#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "py/obj.h"
#include "py/stream.h"
#include "shared-bindings/util.h"
#include "ardupy_util.h"

extern void  common_hal_uart_construct(abstract_module_t *self, size_t n_args, const mp_obj_t * args);
extern void common_hal_uart_deinit(abstract_module_t * self);
extern size_t common_hal_uart_read_bytes(abstract_module_t *self, void *buf_in, mp_uint_t size);
extern size_t common_hal_uart_write_bytes(abstract_module_t *self, const void *buf_in, mp_uint_t size);
extern size_t common_hal_uart_get_buffered_data_len(abstract_module_t *self, size_t * size);

extern const mp_obj_type_t machine_uart_type;

m_generic_make(uart){
    abstract_module_t * self = new_abstruct_module(type);
    mp_arg_check_num(n_args, n_kw, 1, 4, false);
    common_hal_uart_construct(self, n_args, args);
    return self;
}

STATIC mp_obj_t machine_uart_any(mp_obj_t self_in) {
    abstract_module_t * self = (abstract_module_t *)self_in;
    size_t rxbufsize;
    common_hal_uart_get_buffered_data_len(self, &rxbufsize);
    return MP_OBJ_NEW_SMALL_INT(rxbufsize);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(machine_uart_any_obj, machine_uart_any);

STATIC mp_uint_t machine_uart_read(mp_obj_t self_in, void *buf_in, mp_uint_t size, int *errcode) {
    abstract_module_t * self = (abstract_module_t *)self_in;
    
    // make sure we want at least 1 char
    if (size == 0) {
        return 0;
    }
    int bytes_read = common_hal_uart_read_bytes(self, buf_in, size);

    if (bytes_read <= 0) {
        *errcode = MP_EAGAIN;
        return MP_STREAM_ERROR;
    }

    return bytes_read;
}


STATIC mp_uint_t machine_uart_write(mp_obj_t self_in, const void *buf_in, mp_uint_t size, int *errcode) {
    abstract_module_t * self = (abstract_module_t *)self_in;

    int bytes_written = common_hal_uart_write_bytes(self, buf_in, size);

    if (bytes_written < 0) {
        *errcode = MP_EAGAIN;
        return MP_STREAM_ERROR;
    }

    // return number of bytes written
    return bytes_written;
}

STATIC mp_uint_t machine_uart_ioctl(mp_obj_t self_in, mp_uint_t request, mp_uint_t arg, int *errcode) {
    abstract_module_t * self = (abstract_module_t *)self_in;
    mp_uint_t ret;
    if (request == MP_STREAM_POLL) {
        mp_uint_t flags = arg;
        ret = 0;
        size_t rxbufsize;
        common_hal_uart_get_buffered_data_len(self, &rxbufsize);
        if ((flags & MP_STREAM_POLL_RD) && rxbufsize > 0) {
            ret |= MP_STREAM_POLL_RD;
        }
        if ((flags & MP_STREAM_POLL_WR) && 1) { 
            ret |= MP_STREAM_POLL_WR;
        }
    } else {
        *errcode = MP_EINVAL;
        ret = MP_STREAM_ERROR;
    }
    return ret;
}

STATIC const mp_stream_p_t uart_stream_p = {
    .read = machine_uart_read,
    .write = machine_uart_write,
    .ioctl = machine_uart_ioctl,
    .is_text = false,
};

const mp_rom_map_elem_t uart_config_locals_dict_table[] = {
#ifdef SERIAL_5N1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_5N1), MP_ROM_INT(SERIAL_5N1)},
#endif
#ifdef SERIAL_6N1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_6N1), MP_ROM_INT(SERIAL_6N1)},
#endif
#ifdef SERIAL_7N1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_7N1), MP_ROM_INT(SERIAL_7N1)},
#endif
#ifdef SERIAL_8N1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_8N1), MP_ROM_INT(SERIAL_8N1)},
#endif
#ifdef SERIAL_5N2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_5N2), MP_ROM_INT(SERIAL_5N2)},
#endif
#ifdef SERIAL_6N2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_5N1), MP_ROM_INT(SERIAL_6N2)},
#endif
#ifdef SERIAL_7N2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_7N2), MP_ROM_INT(SERIAL_7N2)},
#endif
#ifdef SERIAL_8N2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_8N2), MP_ROM_INT(SERIAL_8N2)},
#endif
#ifdef SERIAL_5E1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_5E1), MP_ROM_INT(SERIAL_5E1)},
#endif
#ifdef SERIAL_6E1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_6E1), MP_ROM_INT(SERIAL_6E1)},
#endif
#ifdef SERIAL_7E1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_7E1), MP_ROM_INT(SERIAL_7E1)},
#endif
#ifdef SERIAL_8E1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_8E1), MP_ROM_INT(SERIAL_8E1)},
#endif
#ifdef SERIAL_5E2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_5E2), MP_ROM_INT(SERIAL_5E2)},
#endif
#ifdef SERIAL_6E2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_6E2), MP_ROM_INT(SERIAL_6E2)},
#endif
#ifdef SERIAL_7E2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_7E2), MP_ROM_INT(SERIAL_7E2)},
#endif
#ifdef SERIAL_8E2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_8E2), MP_ROM_INT(SERIAL_8E2)},
#endif
#ifdef SERIAL_5O1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_5O1), MP_ROM_INT(SERIAL_5N1)},
#endif
#ifdef SERIAL_6O1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_6O1), MP_ROM_INT(SERIAL_6O1)},
#endif
#ifdef SERIAL_7O1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_7O1), MP_ROM_INT(SERIAL_7O1)},
#endif
#ifdef SERIAL_8O1
     {MP_ROM_QSTR(MP_QSTR_SERIAL_8O1), MP_ROM_INT(SERIAL_8O1)},
#endif
#ifdef SERIAL_5O2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_5O2), MP_ROM_INT(SERIAL_5O2)},
#endif
#ifdef SERIAL_6O2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_6O2), MP_ROM_INT(SERIAL_6O2)},
#endif
#ifdef SERIAL_7O2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_7O2), MP_ROM_INT(SERIAL_7O2)},
#endif
#ifdef SERIAL_8O2
     {MP_ROM_QSTR(MP_QSTR_SERIAL_8O2), MP_ROM_INT(SERIAL_8O2)},
#endif
};

MP_DEFINE_CONST_DICT(uart_config_locals_dict, uart_config_locals_dict_table);

const mp_obj_type_t uart_config_type = {
    {&mp_type_type},
    .name = MP_QSTR_config,
    .locals_dict = (mp_obj_t)&uart_config_locals_dict,
};

STATIC const mp_rom_map_elem_t machine_uart_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_deinit),     MP_ROM_PTR(&uart_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__),  MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),   MP_ROM_PTR(&uart_obj___exit___obj) },
    { MP_ROM_QSTR(MP_QSTR_any), MP_ROM_PTR(&machine_uart_any_obj) },
    { MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&mp_stream_read_obj) },
    { MP_ROM_QSTR(MP_QSTR_readline), MP_ROM_PTR(&mp_stream_unbuffered_readline_obj) },
    { MP_ROM_QSTR(MP_QSTR_readinto), MP_ROM_PTR(&mp_stream_readinto_obj) },
    { MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&mp_stream_write_obj) },
    { MP_ROM_QSTR(MP_QSTR_config), MP_ROM_PTR(&uart_config_type) },
};


STATIC MP_DEFINE_CONST_DICT(machine_uart_locals_dict, machine_uart_locals_dict_table);
const mp_obj_type_t machine_uart_type = {
    { &mp_type_type },
    .name = MP_QSTR_UART,
    .make_new = uart_make_new,
    .getiter = mp_identity_getiter,
    .iternext = mp_stream_unbuffered_iter,
    .protocol = &uart_stream_p,
    .locals_dict = (mp_obj_dict_t *)&machine_uart_locals_dict,
};