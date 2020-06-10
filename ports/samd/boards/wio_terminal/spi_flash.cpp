#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include "Adafruit_SPIFlash.h"
extern "C"{
    #include "mpconfigport.h"
    #include "py/objtype.h"
}

Adafruit_FlashTransport_QSPI flashTransport(
            PIN_QSPI_SCK, 
            PIN_QSPI_CS, 
            PIN_QSPI_IO0, 
            PIN_QSPI_IO1, 
            PIN_QSPI_IO2, 
            PIN_QSPI_IO3);
Adafruit_SPIFlash flash((Adafruit_FlashTransport *)& flashTransport);
constexpr int32_t error = 1;
extern "C"{
    int32_t board_flash_read(const volatile void *flash_ptr, void *data, uint32_t size);
    void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len);
    int32_t board_flash_write(const volatile void *flash_ptr, const void *data, uint32_t size) {
        uint32_t len = flash.writeBlocks(
            size_t(flash_ptr) / FILESYSTEM_BLOCK_SIZE, 
            (uint8_t *)data, 
            size / FILESYSTEM_BLOCK_SIZE);
        if (len == 0){
            return error;
        }
        return !error;
    }
    int32_t board_flash_read(const volatile void *flash_ptr, void *data, uint32_t size) {
        uint32_t len = flash.readBlocks(
            size_t(flash_ptr) / FILESYSTEM_BLOCK_SIZE, 
            (uint8_t *)data, 
            size / FILESYSTEM_BLOCK_SIZE);
        if (len == 0){
            return error;
        }
        return !error;
    }
    void board_flash_init() {
        flash.begin();
    }
    void board_flash_flush()
    {
        flash.syncBlocks();
    }
}
