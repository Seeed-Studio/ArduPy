/**
 * The MIT License (MIT)
 *
 * Author: Hongtai Liu (lht856@foxmail.com)
 *
 * Copyright (C) 2020  Seeed Technology Co.,Ltd.
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
#include "Arduino.h"

void *operator new(size_t bytes, void *memory)
{
    return memory;
}
extern "C"
{
#include "lib/utils/pyexec.h"
#include "lib/mp-readline/readline.h"
#include "py/compile.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "py/obj.h"
#include "py/repl.h"
#include "py/runtime.h"
#include "mphalport.h"
#include "ardupy_storage.h"
#include "ardupy_usb.h"

    int mp_hal_stdin_rx_chr(void);
    int mp_hal_stdin_rx_available(void);
    int mp_hal_stdin_rx_peek(void);
    int mp_hal_stdin_rx_read(void);
    void NORETURN __fatal_error(const char *msg);
    void reset()
    {
#if MICROPY_ENABLE_GC
        //the linker varibale
        extern int __ardupy_heap_start__, __ardupy_heap_end__;
        gc_init(&__ardupy_heap_start__, &__ardupy_heap_end__);
#endif

        mp_hal_init();
#if MICROPY_HW_ENABLE_STORAGE
        init_flash_fs();
#endif

        usb_init();
        SerialShow.println("\n\rPress any Key to enter the REPL. Use CTRL-D to soft reboot.\n\r");
    }

    void autoload()
    {
        reset();
        if (mp_import_stat("main.py") != MP_IMPORT_STAT_FILE)
        {
            return;
        }
        SerialShow.println("Auto load main.py by saving files over USB to execute them or enter REPL to disable.\n\r");
        SerialShow.println("main.py output:\n\r");
        pyexec_file("main.py"); // auto load main.py
    }

    void setup()
    {
        SerialShow.begin(115200);
        reset();
        pyexec_file_if_exists("boot.py");
    }
    void loop()
    {

        int exit_code = PYEXEC_FORCED_EXIT;
        bool first_run = true;
        while (true)
        {
            if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL)
            {
                exit_code = pyexec_raw_repl();
            }
            else
            {
                exit_code = pyexec_friendly_repl();
            }

            if (exit_code == PYEXEC_FORCED_EXIT)
            {
                if (!first_run)
                {
                    SerialShow.println("soft reboot");
                }
                first_run = false;
                autoload();
            }
            else
            {
                SerialShow.println("exit_code : " + String(exit_code, HEX));
            }
        }
        mp_deinit();
    }

    void gc_collect(void)
    {
        //the linker variable
        extern int __StackTop;

        // WARNING: This gc_collect implementation doesn't try to get root
        // pointers from CPU registers, and thus may function incorrectly.
        void *dummy;
        gc_collect_start();
        gc_collect_root(&dummy, ((mp_uint_t)&__StackTop - (mp_uint_t)&dummy) / sizeof(mp_uint_t));
        gc_collect_end();
        //gc_dump_info();
    }

    void nlr_jump_fail(void *val)
    {
        printf("FATAL: uncaught exception %p\n", val);
        mp_obj_print_exception(&mp_plat_print, MP_OBJ_FROM_PTR(val));
        __fatal_error("");
    }

    int mp_hal_stdin_rx_chr(void)
    {
        while (true)
        {
            if (msc_save_autoload_tick())
            {
                return CHAR_CTRL_D;
            }
            if (mp_hal_stdin_rx_available())
            {
                int c = mp_hal_stdin_rx_read();
                return c;
            }
        }
    }

    int mp_hal_stdin_rx_available(void)
    {
        return SerialShow.available();
    }

    int mp_hal_stdin_rx_peek(void)
    {
        return SerialShow.peek();
    }

    int mp_hal_stdin_rx_read(void)
    {
        return SerialShow.read();
    }
    void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len)
    {
        if (len)
        {
            SerialShow.write(str, len);
        }
    }
    uintptr_t mp_hal_stdio_poll(uintptr_t poll_flags)
    {
        return 0;
    }
} // extern "C"
