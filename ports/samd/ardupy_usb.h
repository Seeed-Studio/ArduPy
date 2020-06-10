
#ifndef MICROPY_ARDUPY_USB_H
#define MICROPY_ARDUPY_USB_H

#ifdef ARDUINO
#include "Arduino.h"
#endif

extern "C"{
int  mp_hal_get_interrupt_char();
void mp_hal_set_interrupt_char(char c);

void usb_init();
}

#endif