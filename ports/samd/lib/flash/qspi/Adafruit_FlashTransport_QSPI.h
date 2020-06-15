/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 hathach for Adafruit Industries
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

#ifndef ADAFRUIT_FLASHTRANSPORT_QSPI_H_
#define ADAFRUIT_FLASHTRANSPORT_QSPI_H_
#include"Adafruit_FlashTransport.h"

class Adafruit_FlashTransport_QSPI : public Adafruit_FlashTransport
{
  private:
    int8_t _sck, _cs;
    int8_t _io0, _io1, _io2, _io3;

  public:
    Adafruit_FlashTransport_QSPI(int8_t pinSCK, int8_t pinCS, int8_t pinIO0, int8_t pinIO1, int8_t pinIO2, int8_t pinIO3);
    Adafruit_FlashTransport_QSPI(void);

    void begin(void);

    bool supportQuadMode(void) { return true; }

    void setClockSpeed(uint32_t clock_hz);

    bool runCommand(uint8_t command);
    bool readCommand(uint8_t command, uint8_t* response, uint32_t len);
    bool writeCommand(uint8_t command, uint8_t const* data, uint32_t len);

    bool eraseCommand(uint8_t command, uint32_t address);
    bool readMemory(uint32_t addr, uint8_t *data, uint32_t len);
    bool writeMemory(uint32_t addr, uint8_t const *data, uint32_t len);
};

#endif /* ADAFRUIT_FLASHTRANSPORT_QSPI_H_ */
