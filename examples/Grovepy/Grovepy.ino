#include "Arduino.h"

extern "C" {

#include "lib/utils/pyexec.h"
#include "py/compile.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "py/repl.h"
#include "py/runtime.h"

#include "mphalport.h"

static char *stack_top;
#if MICROPY_ENABLE_GC
static char heap[24* 1024];
#endif
void setup() {
#ifdef ARDUINO_ARCH_SAMD
    SerialUSB.begin(115200);
    Serial.begin(115200);
#else
    Serial.begin(115200);
#endif
}
void loop() {
    int stack_dummy;
    stack_top = (char *)&stack_dummy;
#if MICROPY_ENABLE_GC
    gc_init(heap, heap + sizeof(heap));
#endif
    mp_hal_init();
#if MICROPY_ENABLE_COMPILER
#if MICROPY_REPL_EVENT_DRIVEN
    pyexec_event_repl_init();
    for (;;) {
        if (Serial.available()) {
            int c = Serial.read();
            if (pyexec_event_repl_process_char(c)) {
                break;
            }
        }
    }
#else
    for (;;) {
        if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL) {
            if (pyexec_raw_repl() != 0) {
                break;
            }
        } else {
            if (pyexec_friendly_repl() != 0) {
                break;
            }
        }
    }

#endif
    // do_str("print('hello world!', list(x+1 for x in range(10)), end='eol\\n')", MP_PARSE_SINGLE_INPUT);
    // do_str("for i in range(10):\r\n  print(i)", MP_PARSE_FILE_INPUT);
#else
    pyexec_frozen_module("frozentest.py");
#endif

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
    while (1) {
#ifdef ARDUINO_ARCH_SAMD
        SerialUSB.print("nlr_jump_fail\r\n");
#else
        Serial.print("nlr_jump_fail\r\n");
#endif
        delay(1000);
    }
}
// Receive single character
int mp_hal_stdin_rx_chr(void) {
    for (;;) {
#ifdef ARDUINO_ARCH_SAMD
        if (SerialUSB.available()) {
            int c = SerialUSB.read();
            return c;
        }
#else
        if (Serial.available()) {
            int c = Serial.read();
            return c;
        }
#endif
    }
    return 0;
}

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    if (len) {
#ifdef ARDUINO_ARCH_SAMD
        SerialUSB.write(str,len);
#else
        Serial.write(str);
#endif
    }
}

} // extern "C"