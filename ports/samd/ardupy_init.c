/**
 * The MIT License (MIT)
 *
 * Author: Baozhu Zuo (baozhu.zuo@gmail.com)
 *
 * Copyright (C) 2019  Seeed Technology Co.,Ltd.
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
#include <stdio.h>

#include "py/runtime.h"
#include "py/mphal.h"
#include "lib/utils/pyexec.h"
#include "portmodules.h"
// #include "modmachine.h"
#include "extmod/vfs.h"
#include "extmod/utime_mphal.h"
//#include "ardupy_storage.h"

const char grove_help_text[] = "Welcome to MicroPython!\n"
                               "For online help please visit http://micropython.org/help/.\n"
                               "  _____                    _    _____ _             _ _       \n"
                               " / ____|                  | |  / ____| |           | (_)      \n"
                               "| (___   ___  ___  ___  __| | | (___ | |_ _   _  __| |_  ___  \n"
                               " \\___ \\ / _ \\/ _ \\/ _ \\/ _` |  \\___ \\| __| | | |/ _` | |/ _ \\ \n"
                               " ____) |  __/  __/  __/ (_| |  ____) | |_| |_| | (_| | | (_) |\n"
                               "|_____/ \\___|\\___|\\___|\\__,_| |_____/ \\__|\\__,_|\\__,_|_|\\___/ \n"
                               "For further help on a specific object, type help(obj)\n";


extern const struct _mp_obj_type_t ardupy_flash_type;

STATIC mp_obj_t ardupy_fault_debug(mp_obj_t value) {
    //ardupy_hard_fault_debug = mp_obj_is_true(value);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(ardupy_fault_debug_obj, ardupy_fault_debug);

MP_DECLARE_CONST_FUN_OBJ_KW(ardupy_main_obj); // defined in main.c

STATIC const mp_rom_map_elem_t ardupy_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_ardupy) },

    { MP_ROM_QSTR(MP_QSTR_fault_debug), MP_ROM_PTR(&ardupy_fault_debug_obj) },


#if MICROPY_HW_HAS_FLASH
    { MP_ROM_QSTR(MP_QSTR_Flash), MP_ROM_PTR(&ardupy_flash_type) },
#endif

#if MICROPY_HW_ENABLE_SDCARD
    #if MICROPY_PY_ardupy_LEGACY
    { MP_ROM_QSTR(MP_QSTR_SD), MP_ROM_PTR(&ardupy_sdcard_obj) }, // now obsolete
    #endif
    { MP_ROM_QSTR(MP_QSTR_SDCard), MP_ROM_PTR(&ardupy_sdcard_type) },
#endif
};

STATIC MP_DEFINE_CONST_DICT(ardupy_module_globals, ardupy_module_globals_table);

const mp_obj_module_t ardupy_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&ardupy_module_globals,
};

void mp_hal_init() {
    mp_init();
    // mp_obj_list_init(MP_OBJ_TO_PTR(mp_sys_path), 0);
    // mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_)); // current dir (or base dir of the script)
    // mp_obj_list_init(MP_OBJ_TO_PTR(mp_sys_argv), 0);

    mp_obj_list_init(mp_sys_path, 0);
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_)); // current dir (or base dir of the script)
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR__slash_));
    // Frozen modules are in their own pseudo-dir, e.g., ".frozen".
    // Prioritize .frozen over /lib.
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR__dot_frozen));
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR__slash_lib));

    mp_obj_list_init(mp_sys_argv, 0);
    
    readline_init0();
}


void NORETURN __fatal_error(const char *msg) {
    while(1){
        mp_hal_stdout_tx_str(msg);
        mp_hal_stdout_tx_str("\n\r");
        mp_hal_delay_ms(10000000);
    }
}

uint32_t get_fattime(void)
{
    // TODO: Implement this function. For now, fake it.
    return ((2016 - 1980) << 25) | ((12) << 21) | ((4) << 16) | ((00) << 11) | ((18) << 5) | (23 / 2);
}

uint32_t mp_hal_ticks_ms(void) { return millis(); }
uint32_t mp_hal_ticks_us(void) { return micros(); }
uint32_t mp_hal_ticks_cpu(void) { return millis(); }

void mp_hal_delay_ms(mp_uint_t ms)
{
    delay(ms);
}

void mp_hal_delay_us(mp_uint_t us)
{
    delayMicroseconds(us);
}