/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Dan Halbert for Adafruit Industries
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

#ifndef MICROPY_INCLUDED_SHARED_BINDINGS_UTIL_H
#define MICROPY_INCLUDED_SHARED_BINDINGS_UTIL_H

#include "py/runtime.h"
#include "py/obj.h"
#include "py/objstr.h"
#include "py/runtime.h"
#include "py/binary.h"
#include "py/objarray.h"
#include "shared-bindings/util.h"

void normalize_buffer_bounds(int32_t* start, int32_t end, uint32_t* length) {
    if (end < 0) {
        end += *length;
    } else if (((uint32_t) end) > *length) {
        end = *length;
    }   
    if (*start < 0) {
        *start += *length;
    }   
    if (end < *start) {
        *length = 0;
    } else {
        *length = end - *start;
    }   
}     

NORETURN void mp_raise_RuntimeError(const char *msg) {
    mp_raise_msg(&mp_type_RuntimeError, msg);
}
NORETURN void mp_raise_AttributeError(const char *msg) {
    mp_raise_msg(&mp_type_AttributeError, msg);
}

bool try_lock(volatile bool * mutex){
    bool grabbed_lock = false;
    uint32_t state = MICROPY_BEGIN_ATOMIC_SECTION();
    if (!mutex[0]) {
        grabbed_lock = true;
        mutex[0] = true;
    }
    MICROPY_END_ATOMIC_SECTION(state);
    return grabbed_lock;
}

void raise_error_if_not_locked(bool value) {
    if (value) {
        mp_raise_RuntimeError("Function requires lock");
    }
}

// Check if pin is None. If so, deinit() has already been called on the object, so complain.
void raise_error_if_deinited(bool deinited) {
    if (deinited) {
        mp_raise_ValueError("Object has been deinitialized and can no longer be used. Create a new object.");
    }
}
void raise_error_because(const char * msg) {
    mp_raise_ValueError(msg);
}
void raise_error_if(bool reason, const char * msg) {
    if (reason) {
        mp_raise_ValueError(msg);
    }
}


STATIC mp_obj_t default___enter__(mp_obj_t self_in) {
   return self_in;
}
MP_DEFINE_CONST_FUN_OBJ_1(default___enter___obj, default___enter__);                                                                  



// *** Common functions
void generic_method_lookup(mp_obj_t obj, qstr attr, mp_obj_t *dest) {
    mp_obj_type_t *type = mp_obj_get_type(obj);
    if (type->locals_dict != NULL) {
         // generic method lookup
         // this is a lookup in the object (ie not class or type)
         assert(type->locals_dict->base.type == &mp_type_dict); // MicroPython restriction, for now
         mp_map_t *locals_map = &type->locals_dict->map;
         mp_map_elem_t *elem = mp_map_lookup(locals_map, MP_OBJ_NEW_QSTR(attr), MP_MAP_LOOKUP);
         if (elem != NULL) {
             mp_convert_member_lookup(obj, type, elem->value, dest);
         }
    }
}
void* mp_to_ptr(mp_obj_t self_in)
{
    mp_buffer_info_t buffer_info;
    if (self_in == mp_const_none)
        return NULL;

//    if (MP_OBJ_IS_INT(self_in))
//        return (void*)mp_obj_get_int(self_in);

    if (!mp_get_buffer(self_in, &buffer_info, MP_BUFFER_READ)) {
        // No buffer protocol - this is not a Struct or a Blob, it's some other mp object.
        // We only allow setting dict directly, since it's useful to setting user_data for passing data to C.
        // On other cases throw an exception, to avoid a crash later
        if (MP_OBJ_IS_TYPE(self_in, &mp_type_dict))
            return MP_OBJ_TO_PTR(self_in);
        else nlr_raise(
                mp_obj_new_exception_msg_varg(
                    &mp_type_SyntaxError, "Cannot convert '%s' to pointer!", mp_obj_get_type_str(self_in)));
    }

    if (MP_OBJ_IS_STR_OR_BYTES(self_in) || 
        MP_OBJ_IS_TYPE(self_in, &mp_type_bytearray) ||
        MP_OBJ_IS_TYPE(self_in, &mp_type_memoryview))
            return buffer_info.buf;
    else
    {
        void *result;
        if (buffer_info.len != sizeof(result) || buffer_info.typecode != BYTEARRAY_TYPECODE){
            nlr_raise(
                mp_obj_new_exception_msg_varg(
                    &mp_type_SyntaxError, "Cannot convert %s to pointer! (buffer does not represent a pointer)", mp_obj_get_type_str(self_in)));
        }
        memcpy(&result, buffer_info.buf, sizeof(result));
        return result;
    }
}


#endif // MICROPY_INCLUDED_SHARED_BINDINGS_UTIL_H
