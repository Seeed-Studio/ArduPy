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

#include "genhdr/mpversion.h"
#include "py/mpconfig.h"
#include "py/objstr.h"
#include "py/objtuple.h"
#include "py/qstr.h"


mp_obj_t common_hal_os_uname(void) {
    return 0;
}

bool common_hal_os_urandom(uint8_t* buffer, uint32_t length) {
    // #ifdef SAMD51
    // hri_mclk_set_APBCMASK_TRNG_bit(MCLK);
    // struct rand_sync_desc random;
    // rand_sync_init(&random, TRNG);
    // rand_sync_enable(&random);

    // rand_sync_read_buf8(&random, buffer, length);

    // rand_sync_disable(&random);
    // rand_sync_deinit(&random);
    // hri_mclk_clear_APBCMASK_TRNG_bit(MCLK);
    // return true;
    // #else
    // return false;
    // #endif
    return 0;
}
