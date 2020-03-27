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

#ifndef MICROPY_ARDUPY_HAL_PORT_H
#define MICROPY_ARDUPY_HAL_PORT_H

#ifdef ARDUINO
#include "Arduino.h"
#endif
#include "mpconfigport.h"

//#define TOTAL_INTERNAL_FLASH_SIZE 0x010000  //64k
#define TOTAL_INTERNAL_FLASH_SIZE (4096 * 1024)  //4M

//#define INTERNAL_NVM_SIZE 256

#define INTERNAL_FLASH_MEM_SEG1_START_ADDR (0)
#define INTERNAL_FLASH_PART1_NUM_BLOCKS (TOTAL_INTERNAL_FLASH_SIZE / FILESYSTEM_BLOCK_SIZE)

// #define INTERNAL_FLASH_SYSTICK_MASK    (0x1ff) // 512ms
// #define INTERNAL_FLASH_IDLE_TICK(tick) (((tick) & INTERNAL_FLASH_SYSTICK_MASK) == 2)

int  mp_hal_get_interrupt_char();
void mp_hal_set_interrupt_char(char c);
void mp_hal_init();

int32_t board_flash_write(const volatile void *flash_ptr, const void *data, uint32_t size);
int32_t board_flash_read(const volatile void *flash_ptr, void *data, uint32_t size);
void board_flash_init();
//void NORETURN __fatal_error(const char *msg) ;


extern uint32_t mp_hal_ticks_ms(void) ;
extern uint32_t mp_hal_ticks_us(void) ;
extern uint32_t mp_hal_ticks_cpu(void) ;


extern void mp_hal_delay_ms(mp_uint_t ms) ;

extern void mp_hal_delay_us(mp_uint_t ms) ;


#define   GPIO_NUM_0    BCM0
#define   GPIO_NUM_1    BCM1
#define   GPIO_NUM_2    BCM2
#define   GPIO_NUM_3    BCM3
#define   GPIO_NUM_4    BCM4
#define   GPIO_NUM_5    BCM5
#define   GPIO_NUM_6    BCM6
#define   GPIO_NUM_7    BCM7
#define   GPIO_NUM_8    BCM8
#define   GPIO_NUM_9    BCM9
#define   GPIO_NUM_10   BCM10
#define   GPIO_NUM_11   BCM11
#define   GPIO_NUM_12   BCM12
#define   GPIO_NUM_13   BCM13
#define   GPIO_NUM_14   BCM14
#define   GPIO_NUM_15   BCM15
#define   GPIO_NUM_16   BCM16
#define   GPIO_NUM_17   BCM17
#define   GPIO_NUM_18   BCM18
#define   GPIO_NUM_19   BCM19
#define   GPIO_NUM_20   BCM20
#define   GPIO_NUM_21   BCM21
#define   GPIO_NUM_22   BCM22
#define   GPIO_NUM_23   BCM23
#define   GPIO_NUM_24   BCM24
#define   GPIO_NUM_25   BCM25
#define   GPIO_NUM_26   BCM26
#define   GPIO_NUM_27   BCM27
#define   GPIO_NUM_28   PIN_LED_13
#define   GPIO_NUM_29   WIO_BUZZER
#define   GPIO_NUM_30   WIO_LIGHT
#define   GPIO_NUM_31   FPC1
#define   GPIO_NUM_32   FPC2
#define   GPIO_NUM_33   FPC3
#define   GPIO_NUM_34   FPC4
#define   GPIO_NUM_35   FPC5
#define   GPIO_NUM_36   FPC6
#define   GPIO_NUM_37   FPC7
#define   GPIO_NUM_38   FPC8
#define   GPIO_NUM_39   FPC9
#define   GPIO_NUM_40   WIO_MIC
#define   GPIO_NUM_41   BUTTON_1
#define   GPIO_NUM_42   BUTTON_2
#define   GPIO_NUM_43   BUTTON_3
#define   GPIO_NUM_44   WIO_5S_UP
#define   GPIO_NUM_45   WIO_5S_LEFT
#define   GPIO_NUM_46   WIO_5S_RIGHT
#define   GPIO_NUM_47   WIO_5S_DOWM
#define   GPIO_NUM_48   WIO_5S_PRESS



#define    ADC_A0 (27ul) 
#define    ADC_A1 (22ul) 
#define    ADC_A2 (23ul)  
#define    ADC_A3 (24ul)  
#define    ADC_A4 (25ul)  
#define    ADC_A5 (26ul)  
#define    ADC_A6 (13ul)  
#define    ADC_A7 (16ul)  
#define    ADC_A8 (26ul)   

#define    DAC0 (17ul) 
#define    DAC1 (7ul) 

#define PWM0 (27ul) 
#define PWM1 (22ul) 
#define PWM2 (23ul) 
#define PWM3 (13ul) 
#define PWM4 (26ul) 
#define PWM5 (31ul) 
#define PWM6 (32ul) 
#define PWM7 (33ul) 
#define PWM8 (34ul) 
#define PWM9 (38ul) 
#define PWM10 (29ul) 


#endif //
