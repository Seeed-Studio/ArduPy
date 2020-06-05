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

#include "mphalport.h"
#include "hal_init.h"
#include "hal_flash.h"
#include "hpl_pm_base.h"
struct flash_descriptor FLASH_0;

const char grove_help_text[] = "Welcome to MicroPython!\n"
                               "For online help please visit http://micropython.org/help/.\n"
                               "  _____                    _    _____ _             _ _       \n"
                               " / ____|                  | |  / ____| |           | (_)      \n"
                               "| (___   ___  ___  ___  __| | | (___ | |_ _   _  __| |_  ___  \n"
                               " \\___ \\ / _ \\/ _ \\/ _ \\/ _` |  \\___ \\| __| | | |/ _` | |/ _ \\ \n"
                               " ____) |  __/  __/  __/ (_| |  ____) | |_| |_| | (_| | | (_) |\n"
                               "|_____/ \\___|\\___|\\___|\\__,_| |_____/ \\__|\\__,_|\\__,_|_|\\___/ \n"
                               "For further help on a specific object, type help(obj)\n";

#if 0
mp_lexer_t *mp_lexer_new_from_file(const char *filename) {
    mp_raise_OSError(MP_ENOENT);
}
#endif

#include "py/obj.h"
#include "py/mpstate.h"

volatile int mp_interrupt_char = -1;
void * pendsv_object;

void print_hex(uint32_t);
extern int mp_hal_stdin_rx_available(void);
extern int mp_hal_stdin_rx_peek(void);
extern int mp_hal_stdin_rx_read(void);
int mp_hal_get_interrupt_char(){
    return mp_interrupt_char;
}
void usb_invoke(){
    UDD_Handler();

    int token = mp_hal_get_interrupt_char();

    if (token == -1 || !mp_hal_stdin_rx_available()){
        return;
    }
    if (mp_hal_stdin_rx_read() == token){
        pendsv_kbd_intr();
    }
}

void mp_hal_usb_init(){
    USB_SetHandler(&usb_invoke);
}

void mp_hal_set_interrupt_char(char c) {
    if ((signed char)c == -1) {
        mp_obj_exception_clear_traceback(MP_OBJ_FROM_PTR(&MP_STATE_VM(mp_kbd_exception)));
    }
    mp_interrupt_char = (signed char)c;
}

void mp_keyboard_interrupt(void) {
    MP_STATE_VM(mp_pending_exception) = MP_OBJ_FROM_PTR(&MP_STATE_VM(mp_kbd_exception));
    #if MICROPY_ENABLE_SCHEDULER
    if (MP_STATE_VM(sched_state) == MP_SCHED_IDLE) {
        MP_STATE_VM(sched_state) = MP_SCHED_PENDING;
    }
    #endif
}

void pendsv_kbd_intr(){
    if (MP_STATE_VM(mp_pending_exception) == MP_OBJ_NULL) {
        mp_keyboard_interrupt();
    } else {
        MP_STATE_VM(mp_pending_exception) = MP_OBJ_NULL;
        pendsv_object = &MP_STATE_VM(mp_kbd_exception);
        SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
    }
}

// mp_import_stat_t mp_import_stat(const char *path) { return MP_IMPORT_STAT_NO_EXIST; }

// mp_obj_t mp_builtin_open(size_t n_args, const mp_obj_t *args, mp_map_t *kwargs) { return mp_const_none; }
// MP_DEFINE_CONST_FUN_OBJ_KW(mp_builtin_open_obj, 1, mp_builtin_open);

int32_t board_flash_write(const volatile void *flash_ptr, const void *data, uint32_t size) {
    int32_t error_code;
    error_code = flash_erase(&FLASH_0,
                             flash_ptr,
                             FILESYSTEM_BLOCK_SIZE / flash_get_page_size(&FLASH_0));
    if (error_code != 0) {
        return error_code;
    }

    error_code = flash_append(&FLASH_0, flash_ptr, data, FILESYSTEM_BLOCK_SIZE);
  
    return error_code;
}

int32_t board_flash_read(const volatile void *flash_ptr, void *data, uint32_t size) {
    int32_t error_code = flash_read(&FLASH_0, flash_ptr, data, size);
    return error_code;
}
void board_flash_init() {
    _pm_enable_bus_clock(PM_BUS_APBB, NVMCTRL);
    flash_init(&FLASH_0, NVMCTRL);
}

uint32_t get_fattime(void) {
    // TODO: Implement this function. For now, fake it.
    return ((2016 - 1980) << 25) | ((12) << 21) | ((4) << 16) | ((00) << 11) | ((18) << 5) | (23 / 2);
}

uint32_t mp_hal_ticks_ms(void) { return millis(); }
uint32_t mp_hal_ticks_us(void) { return micros(); }
uint32_t mp_hal_ticks_cpu(void) { return millis(); }


void mp_hal_delay_ms(mp_uint_t ms) {
  delay(ms);
}

void mp_hal_delay_us(mp_uint_t us) {
    delayMicroseconds(us);
}