#include <Arduino.h>
#include "Adafruit_SPIFlash.h"
#include "Adafruit_FlashTransport_QSPI.h"
extern "C"{
    #include "py/objtype.h"
}
void * operator new(size_t, void *); 

Adafruit_FlashTransport_QSPI * flashTransport;
Adafruit_SPIFlash * flash;
constexpr int32_t error = 1;
extern "C"{
    
    int32_t board_flash_write(const volatile void *flash_ptr, const void *data, uint32_t size) {
        if (flash->writeBuffer(size_t(flash_ptr), (uint8_t *)data, size) == 0){
            return error;
        }
        return !error;
    }
    int32_t board_flash_read(const volatile void *flash_ptr, void *data, uint32_t size) {
        if (flash->readBuffer(size_t(flash_ptr), (uint8_t *)data, size) == 0){
            return error;
        }
        return !error;
    }
    void board_flash_init() {
        flashTransport = new(m_new_obj(Adafruit_FlashTransport_QSPI)) 
        Adafruit_FlashTransport_QSPI(
            PIN_QSPI_SCK, 
            PIN_QSPI_CS, 
            PIN_QSPI_IO0, 
            PIN_QSPI_IO1, 
            PIN_QSPI_IO2, 
            PIN_QSPI_IO3);
        flash = new(m_new_obj(Adafruit_SPIFlash))
            Adafruit_SPIFlash(flashTransport);
        flash->begin();
    }
}
