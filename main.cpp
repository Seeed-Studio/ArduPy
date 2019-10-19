#include "Arduino.h"

void * operator new(size_t bytes, void * memory){
    return memory;
}

#ifdef USE_GROVE_UI_KEYBOARD
    #include <KeyboardController.h>
    USBHost              usb;
    KeyboardController   keyboard(usb);
#endif

#ifdef USE_GROVE_UI_LCD
    #include "grove_terminal.h"
    grove_terminal     terminal;
#endif

#if defined(SEEEDUINO_MO)
    #define SerialShow SerialUSB
#else if defined(SEEED_GROVE_UI_WIRELESS)
    #define SerialShow Serial
#endif

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

    int mp_hal_stdin_rx_chr(void);
    int mp_hal_stdin_rx_available(void);
    int mp_hal_stdin_rx_peek(void);
    int mp_hal_stdin_rx_read(void);
    void NORETURN __fatal_error(const char *msg);
    void reset(){
        #if MICROPY_ENABLE_GC
            //the linker varibale
            extern int __ardupy_heap_start__, __ardupy_heap_end__;
            gc_init(&__ardupy_heap_start__, &__ardupy_heap_end__);
        #endif
            mp_hal_init();
        #if MICROPY_HW_ENABLE_STORAGE
            init_flash_fs();
        #endif
    }
    void setup() {
        #ifdef USE_GROVE_UI_KEYBOARD
            usb.Init();
        #endif

        #ifdef USE_GROVE_UI_LCD
            terminal.begin();
        #endif

        #if not defined USE_GROVE_UI_KEYBOARD || not defined USE_GROVE_UI_LCD
            SerialShow.begin(115200);
        #endif
    }
    void loop() {
        int exit_code = PYEXEC_FORCED_EXIT;
        reset();
        pyexec_file_if_exists("boot.py");

        #if MICROPY_ENABLE_COMPILER
            #if MICROPY_REPL_EVENT_DRIVEN
                pyexec_event_repl_init(); 

                while (true) {
                    int c = mp_hal_stdin_rx_chr();
                    if (pyexec_event_repl_process_char(c)) {
                        break;
                    }
                }
        #else
            while(true) {
                if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL) {
                    exit_code = pyexec_raw_repl();
                } 
                else {
                    exit_code = pyexec_friendly_repl();
                    reset();
                }
                if (exit_code == PYEXEC_FORCED_EXIT) {
                    SerialShow.println("soft reboot");
                }
                else{
                    SerialShow.println("exit_code : " + String(exit_code, HEX));
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
        //the linker variable
        extern int __StackTop;

        // WARNING: This gc_collect implementation doesn't try to get root
        // pointers from CPU registers, and thus may function incorrectly.
        void *dummy;
        gc_collect_start();
        gc_collect_root(&dummy, ((mp_uint_t)&__StackTop - (mp_uint_t)&dummy) / sizeof(mp_uint_t));
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

    int mp_hal_stdin_rx_chr(void) {
        while(true) {
            if (mp_hal_stdin_rx_available()) {
                int c = mp_hal_stdin_rx_read();
                return c;
            }
        }
    }

    #ifdef USE_GROVE_UI_KEYBOARD
        char key;
        void keyPressed() {}

        // This function intercepts key release
        void keyReleased() {
            key = keyboard.getKey();
            switch(keyboard.getModifiers()){
            case LeftCtrl:
            case RightCtrl:
                if ('a' <= key && key <= 'd'){
                    key -= 'a' + 1;
                }
                else if ('A' <= key && key <= 'D'){
                    key -= 'A' + 1;
                }
                break;
            default:
                key = 0;
                break;
            }
        }

        int mp_hal_stdin_rx_available(void){
            usb.Task();
            return key != 0;
        }

        int mp_hal_stdin_rx_peek(void){
            return key;
        }

        int mp_hal_stdin_rx_read(void){
            auto temp = key;
            return key;
        }
    #else
        int mp_hal_stdin_rx_available(void){
            return SerialShow.available();
        }

        int mp_hal_stdin_rx_peek(void){
            return SerialShow.peek();
        }

        int mp_hal_stdin_rx_read(void){
            return SerialShow.read();
        }
    #endif

    #ifdef USE_GROVE_UI_LCD
        void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
            if (len) {
                terminal.print(str, uint32_t(len));
            }
        }
    #else
        void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
            if (len) {
                SerialShow.write(str, len);
            }
        }
    #endif

    uintptr_t mp_hal_stdio_poll(uintptr_t poll_flags) {
        return 0;
    }
} // extern "C"
