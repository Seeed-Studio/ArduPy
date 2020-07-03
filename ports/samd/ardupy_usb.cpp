/**
 * The MIT License (MIT)
 *
 * Author: Hongtai Liu (lht856@foxmail.com)
 *
 * Copyright (C) 2020  Seeed Technology Co.,Ltd.
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

#include "ardupy_usb.h"
#include "Adafruit_TinyUSB.h"
Adafruit_USBD_MSC usb_msc;
#define SAVE_AUTOLOAD_TICKS 300
extern "C"
{
#include "py/compile.h"
#include "py/obj.h"
#include "py/mpstate.h"
#include "ardupy_storage.h"
#include "lib/mp-readline/readline.h"
#include "lib/utils/pyexec.h"
#include "py/gc.h"
#include "mphalport.h"

    void *pendsv_object;
    // USB Mass Storage object
    volatile int mp_interrupt_char = -1;

    volatile int msc_save_trigger = 0;      // msc save trigger flag
    volatile uint32_t msc_save_timeout = 0; // msc save auto load timeout
    volatile uint32_t msc_save_ticks = 0;   // msc save ticks
    volatile uint32_t msc_save_autoload = 0;

    extern void reset();

    void mp_keyboard_interrupt(void)
    {
        MP_STATE_VM(mp_pending_exception) = MP_OBJ_FROM_PTR(&MP_STATE_VM(mp_kbd_exception));
#if MICROPY_ENABLE_SCHEDULER
        if (MP_STATE_VM(sched_state) == MP_SCHED_IDLE)
        {
            MP_STATE_VM(sched_state) = MP_SCHED_PENDING;
        }
#endif
    }

    void pendsv_kbd_intr()
    {
        if (MP_STATE_VM(mp_pending_exception) == MP_OBJ_NULL)
        {
            mp_keyboard_interrupt();
        }
        else
        {
            MP_STATE_VM(mp_pending_exception) = MP_OBJ_NULL;
            pendsv_object = &MP_STATE_VM(mp_kbd_exception);
            SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
        }
    }

    /**
    * Callback invoked when received an "wanted" char.
    * @param itf           Interface index (for multiple cdc interfaces)
    * @param wanted_char   The wanted char (set previously)
    */
    void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char)
    {
        (void)itf; // not used

        // Compare mp_interrupt_char with wanted_char and ignore if not matched
        if (mp_interrupt_char == wanted_char)
        {
            tud_cdc_read_flush(); // flush read fifo
            pendsv_kbd_intr();
        }
    }

    void mp_hal_set_interrupt_char(char c)
    {
        if ((signed char)c == -1)
        {
            mp_obj_exception_clear_traceback(MP_OBJ_FROM_PTR(&MP_STATE_VM(mp_kbd_exception)));
        }
        mp_interrupt_char = (signed char)c;
    }

    // Callback invoked when received READ10 command.
    // Copy disk's data to buffer (up to bufsize) and
    // return number of copied bytes (must be multiple of block size)
    int32_t msc_read_cb(uint32_t lba, void *buffer, uint32_t bufsize)
    {
        return storage_read_blocks((uint8_t *)buffer, lba, bufsize / 512) == 0 ? bufsize : -1;
    }
    // Callback invoked when received WRITE10 command.
    // Process data in buffer to disk's storage and
    // return number of written bytes (must be multiple of block size)
    int32_t msc_write_cb(uint32_t lba, uint8_t *buffer, uint32_t bufsize)
    {
        return storage_write_blocks((uint8_t *)buffer, lba, bufsize / 512) == 0 ? bufsize : -1;
    }

    // Callback invoked when WRITE10 command is completed (status received and accepted by host).
    // used to flush any pending cache.
    void msc_flush_cb(void)
    {
        storage_flush();
        // trigger msc save event
        if (msc_save_trigger == 0)
        {
            tud_cdc_read_flush(); // flush read fifo
            pendsv_kbd_intr();
            msc_save_trigger = 1;
            msc_save_ticks = mp_hal_ticks_ms();
        }
        msc_save_timeout = SAVE_AUTOLOAD_TICKS;
    } 

    bool msc_save_autoload_tick(void)
    {
        if (msc_save_trigger == 1)
        {
            uint32_t tick = mp_hal_ticks_ms() - msc_save_ticks;
            msc_save_ticks = mp_hal_ticks_ms();
            if (tick != 0)
            {
                if ((msc_save_timeout -= tick) == 0) // if time out
                {
                    msc_save_trigger = 0;
                    return true;
                }
            }
        }
        return false;
    }

    void usb_init()
    {
        // Set key interrupt char CHAR_CTRL_C(0x03)
        tud_cdc_set_wanted_char(CHAR_CTRL_C);

        // Set disk vendor id, product id and revision with string up to 8, 16, 4 characters respectively
        usb_msc.setID("Seeeduino", "Ardupy", "1.0");

        // Set callback
        usb_msc.setReadWriteCallback(msc_read_cb, msc_write_cb, msc_flush_cb);

        // Set disk size, block size should be 512 regardless of spi flash page size
        usb_msc.setCapacity(storage_get_block_count(), storage_get_block_size());

        // MSC is ready for read/write
        usb_msc.setUnitReady(true);

        usb_msc.begin();
        
    }
}
