#include "submodule/Grove_LED_Bar.h"
extern "C"{
#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/util.h"
}

#define $ (*(Grove_LED_Bar *)self)
void * operator new(size_t, void *); 

namespace {
    void * new_led_bar(
        void ** get, 
        const mcu_pin_obj_t * pin_clk, 
        const mcu_pin_obj_t * pin_dat){
        *get = new(m_new_obj(Grove_LED_Bar)) Grove_LED_Bar(
            pin_clk->number, 
            pin_dat->number, 
            0, 
            LED_BAR_10
        );
    }
}

extern "C" {
    void common_hal_led_bar_construct(
        void ** get, 
        const mcu_pin_obj_t * pin_clk, 
        const mcu_pin_obj_t * pin_dat){
        new_led_bar(get, pin_clk, pin_dat);
    }
    void common_hal_led_bar_deinit(void *self){

    }
    void common_hal_led_bar_get_led_numbers(void *self, uint32_t * value){
        Origin::LedDevice * dev = (Origin::LedDevice *)self;
        *value = dev->countOfLed();
    }
    void common_hal_led_bar_set_bits(void *self, uint32_t value){
        $.setBits(value);
    }
    void common_hal_led_bar_get_bits(void *self, uint32_t * value){
        *value = $.getBits();
    }
    void common_hal_led_bar_set_level(void *self, float value){
        $.setLevel(value);
    }
    void common_hal_led_bar_set_brightness(void *self, uint32_t led_no, float value){
        $.setLed(led_no, value);
    }
    void common_hal_led_bar_set_is_reverse_show(void *self, uint32_t value){
        $.setGreenToRed(value != 0);
    }
    void common_hal_led_bar_toggle(void *self, uint32_t led_no){
        $.toggleLed(led_no);
    }
}