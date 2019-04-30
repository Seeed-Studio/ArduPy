#include "py/compile.h"
#include "py/runtime.h"
#include "py/repl.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "lib/utils/pyexec.h"

#include "Arduino.h"
static inline void mp_hal_set_interrupt_char(char c) {}
void mp_hal_init();