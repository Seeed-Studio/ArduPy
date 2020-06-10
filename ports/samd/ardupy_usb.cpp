#include "ardupy_usb.h"
#include "Adafruit_TinyUSB.h"
Adafruit_USBD_MSC usb_msc;
extern "C"
{
#include "py/obj.h"
#include "py/mpstate.h"
#include "ardupy_storage.h"
#include "lib/mp-readline/readline.h"

    void *pendsv_object;
    // USB Mass Storage object
    volatile int mp_interrupt_char = -1;

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
    }

    void usb_init()
    {
        // Set key interrupt char CHAR_CTRL_C(0x03)
        tud_cdc_set_wanted_char(CHAR_CTRL_C);

        // Set disk vendor id, product id and revision with string up to 8, 16, 4 characters respectively
        usb_msc.setID("Seeeduino", "ArduPy", "1.0");

        // Set callback
        usb_msc.setReadWriteCallback(msc_read_cb, msc_write_cb, msc_flush_cb);

        // Set disk size, block size should be 512 regardless of spi flash page size
        usb_msc.setCapacity(storage_get_block_count(), storage_get_block_size());

        // MSC is ready for read/write
        usb_msc.setUnitReady(true);
    
        usb_msc.begin();
    }
}