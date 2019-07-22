#include "Arduino.h"
extern "C" {

#include "lib/utils/pyexec.h"
#include "py/compile.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "py/obj.h"
#include "py/repl.h"
#include "py/runtime.h"

#include "mphalport.h"
#include "ardupy_storage.h"

#define SerialShow SerialUSB
void NORETURN __fatal_error(const char *msg);
static char *stack_top;

void reset(){
#if MICROPY_ENABLE_GC
    extern int __ardupy_heap_start__, __ardupy_heap_end__;
    gc_init(&__ardupy_heap_start__, &__ardupy_heap_end__);
#endif
    mp_hal_init();
#if MICROPY_HW_ENABLE_STORAGE
    init_flash_fs();
#endif
}

void setup() {
    SerialShow.begin(115200);
}
void loop() {
    int stack_dummy;
    int exit_code = PYEXEC_FORCED_EXIT;
    bool first_run = true;
    stack_top = (char *)&stack_dummy;

    reset();

#if MICROPY_ENABLE_COMPILER
#if MICROPY_REPL_EVENT_DRIVEN
    pyexec_event_repl_init();
    for (;;) {
        if (SerialShow.available()) {
            int c = SerialShow.read();
            if (pyexec_event_repl_process_char(c)) {
                break;
            }
        }
    }
#else
    for (;;) {
        if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL) {
            exit_code = pyexec_raw_repl();
        } else {
            exit_code = pyexec_friendly_repl();
            reset();
        }
        if (exit_code == PYEXEC_FORCED_EXIT) {
            SerialShow.println("soft reboot");
        }else
        {
            SerialShow.println("exit_code:  " + String(exit_code,HEX));
        }
        
    }

#endif
    // do_str("print('hello world!', list(x+1 for x in range(10)), end='eol\\n')", MP_PARSE_SINGLE_INPUT);
    // do_str("for i in range(10):\r\n  print(i)", MP_PARSE_FILE_INPUT);
#else
    pyexec_frozen_module("frozentest.py");
#endif
    SerialShow.print("soft reboot\r\n");

    mp_deinit();
}

void gc_collect(void) {
    // WARNING: This gc_collect implementation doesn't try to get root
    // pointers from CPU registers, and thus may function incorrectly.
    void *dummy;
    gc_collect_start();
    gc_collect_root(&dummy, ((mp_uint_t)stack_top - (mp_uint_t)&dummy) / sizeof(mp_uint_t));
    gc_collect_end();
    gc_dump_info();
}

void nlr_jump_fail(void *val) {
    printf("FATAL: uncaught exception %p\n", val);
    mp_obj_print_exception(&mp_plat_print, MP_OBJ_FROM_PTR(val));
    __fatal_error("");
#if 0
    while (1) {
#ifdef ARDUINO_ARCH_SAMD
        SerialUSB.print("nlr_jump_fail\r\n");
#else
        Serial.print("nlr_jump_fail\r\n");
#endif
        delay(1000);
    }
#endif
}
// Receive single character
int mp_hal_stdin_rx_chr(void) {
    for (;;) {
        if (SerialShow.available()) {
            int c = SerialShow.read();
            return c;
        }

    }
    return 0;
}

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    if (len) {
        SerialShow.write(str, len);
    }
}

} // extern "C"