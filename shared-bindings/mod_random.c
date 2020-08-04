/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Paul Sokolovsky
 * Copyright (c) 2016 Scott Shawcroft for Adafruit Industries
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

#include <assert.h>
#include <string.h>

#include "py/obj.h"
#include "py/runtime.h"
#include "shared-bindings/mod_random.h"

#ifdef ARDUINO
#include "Arduino.h"
#endif

inline uint64_t common_hal_time_monotonic() {
    //return ticks_ms;
    return millis();

}

STATIC uint32_t yasmarang_pad = 0xeda4baba, yasmarang_n = 69, yasmarang_d = 233;
STATIC uint8_t yasmarang_dat = 0;

STATIC uint32_t yasmarang(void)
{
    if (yasmarang_pad == 0xeda4baba) {
        yasmarang_pad = common_hal_time_monotonic() & 0xffffffff;
    }
   yasmarang_pad += yasmarang_dat + yasmarang_d * yasmarang_n;
   yasmarang_pad = (yasmarang_pad<<3) + (yasmarang_pad>>29);
   yasmarang_n = yasmarang_pad | 2;
   yasmarang_d ^= (yasmarang_pad<<31) + (yasmarang_pad>>1);
   yasmarang_dat ^= (char) yasmarang_pad ^ (yasmarang_d>>8) ^ 1;

   return (yasmarang_pad^(yasmarang_d<<5)^(yasmarang_pad>>18)^(yasmarang_dat<<1));
}  /* yasmarang */

// End of Yasmarang

// returns an unsigned integer below the given argument
// n must not be zero
STATIC uint32_t yasmarang_randbelow(uint32_t n) {
    uint32_t mask = 1;
    while ((n & mask) < n) {
        mask = (mask << 1) | 1;
    }
    uint32_t r;
    do {
        r = yasmarang() & mask;
    } while (r >= n);
    return r;
}

void shared_modules_random_seed(mp_uint_t seed) {
    yasmarang_pad = seed;
    yasmarang_n = 69;
    yasmarang_d = 233;
    yasmarang_dat = 0;
}

mp_uint_t shared_modules_random_getrandbits(uint8_t n) {
    uint32_t mask = ~0;
    // Beware of C undefined behavior when shifting by >= than bit size
    mask >>= (32 - n);
    return yasmarang() & mask;
}

mp_int_t shared_modules_random_randrange(mp_int_t start, mp_int_t stop, mp_int_t step) {
    mp_int_t n;
    if (step > 0) {
        n = (stop - start + step - 1) / step;
    } else {
        n = (stop - start + step + 1) / step;
    }
    return start + step * yasmarang_randbelow(n);
}

// returns a number in the range [0..1) using Yasmarang to fill in the fraction bits
STATIC mp_float_t yasmarang_float(void) {
    #if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_DOUBLE
    typedef uint64_t mp_float_int_t;
    #elif MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT
    typedef uint32_t mp_float_int_t;
    #endif
    union {
        mp_float_t f;
        #if MP_ENDIANNESS_LITTLE
        struct { mp_float_int_t frc:MP_FLOAT_FRAC_BITS, exp:MP_FLOAT_EXP_BITS, sgn:1; } p;
        #else
        struct { mp_float_int_t sgn:1, exp:MP_FLOAT_EXP_BITS, frc:MP_FLOAT_FRAC_BITS; } p;
        #endif
    } u;
    u.p.sgn = 0;
    u.p.exp = (1 << (MP_FLOAT_EXP_BITS - 1)) - 1;
    if (MP_FLOAT_FRAC_BITS <= 32) {
        u.p.frc = yasmarang();
    } else {
        u.p.frc = ((uint64_t)yasmarang() << 32) | (uint64_t)yasmarang();
    }
    return u.f - 1;
}

mp_float_t shared_modules_random_random(void) {
    return yasmarang_float();
}

mp_float_t shared_modules_random_uniform(mp_float_t a, mp_float_t b) {
    return a + (b - a) * yasmarang_float();
}


//| :mod:`random` --- psuedo-random numbers and choices
//| ========================================================
//|
//| .. module:: random
//|   :synopsis: psuedo-random numbers and choices
//|   :platform: SAMD21, ESP8266
//|
//| The `random` module is a strict subset of the CPython `cpython:random`
//| module. So, code written in CircuitPython will work in CPython but not
//| necessarily the other way around.
//|
//| Like its CPython cousin, CircuitPython's random seeds itself on first use
//| with a true random from os.urandom() when available or the uptime otherwise.
//| Once seeded, it will be deterministic, which is why its bad for cryptography.
//|
//| .. warning:: Numbers from this module are not cryptographically strong! Use
//|   bytes from `os.urandom` directly for true randomness.
//|

//| .. function:: seed(seed)
//|
//|   Sets the starting seed of the random  number generation. Further calls to
//|   `random` will return deterministic results afterwards.
//|
STATIC mp_obj_t random_seed(mp_obj_t seed_in) {
    mp_uint_t seed = mp_obj_get_int_truncated(seed_in);
    shared_modules_random_seed(seed);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(random_seed_obj, random_seed);

//| .. function:: getrandbits(k)
//|
//|   Returns an integer with *k* random bits.
//|
STATIC mp_obj_t random_getrandbits(mp_obj_t num_in) {
    int n = mp_obj_get_int(num_in);
    if (n > 32 || n == 0) {
        mp_raise_ValueError(NULL);
    }
    return mp_obj_new_int_from_uint(shared_modules_random_getrandbits((uint8_t) n));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(random_getrandbits_obj, random_getrandbits);

//| .. function:: randrange(stop)
//|               randrange(start, stop, step=1)
//|
//|   Returns a randomly selected integer from ``range(start, stop, step)``.
//|
STATIC mp_obj_t random_randrange(size_t n_args, const mp_obj_t *args) {
    mp_int_t start = 0;
    mp_int_t stop = mp_obj_get_int(args[0]);
    mp_int_t step = 1;
    if (n_args == 1) {
        // range(stop)
        if (stop <= 0) {
            mp_raise_ValueError("stop not reachable from start");
        }
    } else {
        start = stop;
        stop = mp_obj_get_int(args[1]);
        if (n_args == 2) {
            // range(start, stop)
            if (start >= stop) {
                mp_raise_ValueError("stop not reachable from start");
            }
        } else {
            // range(start, stop, step)
            step = mp_obj_get_int(args[2]);
            mp_int_t n;
            if (step > 0) {
                n = (stop - start + step - 1) / step;
            } else if (step < 0) {
                n = (stop - start + step + 1) / step;
            } else {
                mp_raise_ValueError("step must be non-zero");
            }
            if (n <= 0) {
                mp_raise_ValueError("invalid step");
            }
        }
    }

    return mp_obj_new_int(shared_modules_random_randrange(start, stop, step));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(random_randrange_obj, 1, 3, random_randrange);

//| .. function:: randint(a, b)
//|
//|   Returns a randomly selected integer between a and b inclusive. Equivalent
//|   to ``randrange(a, b + 1, 1)``
//|
STATIC mp_obj_t random_randint(mp_obj_t a_in, mp_obj_t b_in) {
    mp_int_t a = mp_obj_get_int(a_in);
    mp_int_t b = mp_obj_get_int(b_in);
    if (a > b) {
        mp_raise_ValueError(NULL);
    }
    return mp_obj_new_int(shared_modules_random_randrange(a, b + 1, 1));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(random_randint_obj, random_randint);

//| .. function:: choice(seq)
//|
//|   Returns a randomly selected element from the given sequence. Raises
//|   IndexError when the sequence is empty.
//|
STATIC mp_obj_t random_choice(mp_obj_t seq) {
    mp_int_t len = mp_obj_get_int(mp_obj_len(seq));
    if (len == 0) {
        mp_raise_RuntimeError("empty sequence");
    }
    return mp_obj_subscr(seq, mp_obj_new_int(shared_modules_random_randrange(0, len, 1)), MP_OBJ_SENTINEL);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(random_choice_obj, random_choice);

//| .. function:: random()
//|
//|   Returns a random float between 0 and 1.0.
//|
STATIC mp_obj_t random_random(void) {
    return mp_obj_new_float(shared_modules_random_random());
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(random_random_obj, random_random);

//| .. function:: uniform(a, b)
//|
//|   Returns a random float between a and b. It may or may not be inclusive
//|   depending on float rounding.
//|
STATIC mp_obj_t random_uniform(mp_obj_t a_in, mp_obj_t b_in) {
    mp_int_t a = mp_obj_get_float(a_in);
    mp_int_t b = mp_obj_get_float(b_in);
    return mp_obj_new_float(shared_modules_random_uniform(a, b));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(random_uniform_obj, random_uniform);

STATIC const mp_rom_map_elem_t mp_module_random_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_random) },
    { MP_ROM_QSTR(MP_QSTR_seed), MP_ROM_PTR(&random_seed_obj) },
    { MP_ROM_QSTR(MP_QSTR_getrandbits), MP_ROM_PTR(&random_getrandbits_obj) },
    { MP_ROM_QSTR(MP_QSTR_randrange), MP_ROM_PTR(&random_randrange_obj) },
    { MP_ROM_QSTR(MP_QSTR_randint), MP_ROM_PTR(&random_randint_obj) },
    { MP_ROM_QSTR(MP_QSTR_choice), MP_ROM_PTR(&random_choice_obj) },
    { MP_ROM_QSTR(MP_QSTR_random), MP_ROM_PTR(&random_random_obj) },
    { MP_ROM_QSTR(MP_QSTR_uniform), MP_ROM_PTR(&random_uniform_obj) },
};

STATIC MP_DEFINE_CONST_DICT(mp_module_random_globals, mp_module_random_globals_table);

const mp_obj_module_t random_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_random_globals,
};
