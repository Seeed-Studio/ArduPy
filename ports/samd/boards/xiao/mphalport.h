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

#define TOTAL_INTERNAL_FLASH_SIZE 0xC000 //48K

#define INTERNAL_NVM_SIZE 256

#define INTERNAL_FLASH_MEM_SEG1_START_ADDR (FLASH_SIZE - TOTAL_INTERNAL_FLASH_SIZE - INTERNAL_NVM_SIZE)
#define INTERNAL_FLASH_PART1_NUM_BLOCKS (TOTAL_INTERNAL_FLASH_SIZE / FILESYSTEM_BLOCK_SIZE)

int mp_hal_get_interrupt_char();
void mp_hal_set_interrupt_char(char c);
void mp_hal_init();

int32_t board_flash_write(const volatile void *flash_ptr, const void *data, uint32_t size);
int32_t board_flash_read(const volatile void *flash_ptr, void *data, uint32_t size);
void board_flash_init();
void board_flash_flush();

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
#define GPIO_NUM_0 (0ul)
#define GPIO_NUM_1 (1ul)
#define GPIO_NUM_2 (2ul)
#define GPIO_NUM_3 (3ul)
#define GPIO_NUM_4 (4ul)
#define GPIO_NUM_5 (5ul)
#define GPIO_NUM_6 (6ul)
#define GPIO_NUM_7 (7ul)
#define GPIO_NUM_8 (8ul)
#define GPIO_NUM_9 (9ul)
#define GPIO_NUM_10 (10ul)
#define GPIO_NUM_11 (11ul)
#define GPIO_NUM_12 (12ul)
#define GPIO_NUM_13 (13ul)

#ifndef UART_INTERFACES_COUNT
#define UART_INTERFACES_COUNT 2
#endif

#endif //
