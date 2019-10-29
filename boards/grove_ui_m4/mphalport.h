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


#include "Arduino.h"
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

#endif //
