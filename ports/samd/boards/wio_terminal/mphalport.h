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

#define SerialShow Serial

#define TOTAL_INTERNAL_FLASH_SIZE (4096 * 1024) //4M

#define INTERNAL_FLASH_MEM_SEG1_START_ADDR (0)
#define INTERNAL_FLASH_PART1_NUM_BLOCKS (TOTAL_INTERNAL_FLASH_SIZE / FILESYSTEM_BLOCK_SIZE)

int32_t board_flash_write(const volatile void *flash_ptr, const void *data, uint32_t size);
int32_t board_flash_read(const volatile void *flash_ptr, void *data, uint32_t size);
void board_flash_init();
void board_flash_flush();

void mp_hal_init();
//void NORETURN __fatal_error(const char *msg) ;

extern uint32_t mp_hal_ticks_ms(void);
extern uint32_t mp_hal_ticks_us(void);
extern uint32_t mp_hal_ticks_cpu(void);

extern void mp_hal_delay_ms(mp_uint_t ms);

extern void mp_hal_delay_us(mp_uint_t ms);

/*
*Pin mapping from Arduino to ArduPy
* 
*/
#define GPIO_NUM_0 -1
#define GPIO_NUM_1 -1
#define GPIO_NUM_2 -1
#define GPIO_NUM_3 BCM2
#define GPIO_NUM_4 -1
#define GPIO_NUM_5 BCM3
#define GPIO_NUM_6 -1
#define GPIO_NUM_7 BCM4
#define GPIO_NUM_8 BCM14
#define GPIO_NUM_9 -1
#define GPIO_NUM_10 BCM15
#define GPIO_NUM_11 BCM17
#define GPIO_NUM_12 BCM18
#define GPIO_NUM_13 BCM27
#define GPIO_NUM_14 -1
#define GPIO_NUM_15 BCM22
#define GPIO_NUM_16 BCM23
#define GPIO_NUM_17 -1
#define GPIO_NUM_18 BCM24
#define GPIO_NUM_19 BCM10
#define GPIO_NUM_20 -1
#define GPIO_NUM_21 BCM9
#define GPIO_NUM_22 BCM25
#define GPIO_NUM_23 BCM11
#define GPIO_NUM_24 BCM7
#define GPIO_NUM_25 -1
#define GPIO_NUM_26 BCM7
#define GPIO_NUM_27 BCM0
#define GPIO_NUM_28 BCM1
#define GPIO_NUM_29 BCM5
#define GPIO_NUM_30 -1
#define GPIO_NUM_31 BCM6
#define GPIO_NUM_32 BCM12
#define GPIO_NUM_33 BCM13
#define GPIO_NUM_34 -1
#define GPIO_NUM_35 BCM19
#define GPIO_NUM_36 BCM16
#define GPIO_NUM_37 BCM26
#define GPIO_NUM_38 BCM20
#define GPIO_NUM_39 -1
#define GPIO_NUM_40 BCM21
#define GPIO_NUM_41 FPC1
#define GPIO_NUM_42 FPC2
#define GPIO_NUM_43 FPC3
#define GPIO_NUM_44 FPC4
#define GPIO_NUM_45 FPC5
#define GPIO_NUM_46 FPC6
#define GPIO_NUM_47 FPC7
#define GPIO_NUM_48 FPC8
#define GPIO_NUM_49 FPC9
#define GPIO_NUM_50 PIN_LED_13
#define GPIO_NUM_51 WIO_BUZZER
#define GPIO_NUM_52 WIO_LIGHT
#define GPIO_NUM_53 WIO_MIC
#define GPIO_NUM_54 WIO_IR
#define GPIO_NUM_55 BUTTON_1
#define GPIO_NUM_56 BUTTON_2
#define GPIO_NUM_57 BUTTON_3
#define GPIO_NUM_58 WIO_5S_UP
#define GPIO_NUM_59 WIO_5S_LEFT
#define GPIO_NUM_60 WIO_5S_RIGHT
#define GPIO_NUM_61 WIO_5S_DOWN
#define GPIO_NUM_62 WIO_5S_PRESS

#ifndef UART_INTERFACES_COUNT
#define UART_INTERFACES_COUNT 2
#endif

#endif //
