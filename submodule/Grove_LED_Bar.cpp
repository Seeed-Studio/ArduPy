/*
  LED bar library V2.0
  Copyright (c) 2010 Seeed Technology Inc.

  Original Author: LG

  Modify: Loovee, 2014-2-26
  User can choose which Io to be used.

  The MIT License (MIT)

  Copyright (c) 2013 Seeed Technology Inc.

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifdef _MSC_BUILD
#include<stdint.h>
#endif

#include "Grove_LED_Bar.h"

enum LedState {
    LED_TURN_OFF,
    LED_FULL_BRIGHTNESS = 0xFF,
};

namespace Origin {
    LedDevice::LedDevice(uint32_t pinClock, uint32_t pinData, bool reverseShow, LedType type) {
        this->pinClock = pinClock;
        this->pinData = pinData;
        this->reverseShow = reverseShow;
        this->type = type;
        this->countOfShows = countOfLed();

        for (uint32_t i = 0; i < LED_MAX_COUNT; i++) {
            led[i] = LED_TURN_OFF;
        }

        pinMode(pinClock, OUTPUT);
        pinMode(pinData, OUTPUT);
    }
    uint32_t LedDevice::countOfLed() {
        return (uint32_t)type & LED_TYPE_MASK;
    }
    void LedDevice::send(uint16_t bits) {
        for (uint32_t i = 0, clk = 0; i < 16; i++) {
            digitalWrite(pinData, bits & 0x8000 ? HIGH : LOW);
            digitalWrite(pinClock, clk);
            clk = ~clk;
            bits <<= 1;
        }
    }
    void LedDevice::send() {
        if (reverseShow) {
            if (LED_BAR_10 != type) {
                send(0x00); //send cmd(0x00)

                for (uint32_t i = 24; i-- > 12; ) {
                    send(led[i]);
                }

                send(0x00); //send cmd(0x00)

                for (uint32_t i = 12; i-- > 0; ) {
                    send(led[i]);
                }
            }
            else {
                send(0x00); //send cmd(0x00)

                for (uint32_t i = countOfShows; i-- > 0; ) {
                    send(led[i]);
                }
                for (uint32_t i = 0; i < 12 - countOfShows; i++) {
                    send(0x00);
                }
            }

        }
        else {
            send(0x00); //send cmd(0x00)
            
            for (uint32_t i = 0; i < 12; i++) {
                send(led[i]);
            }

            if (LED_BAR_10 == type) {
                latch();
                return;
            }

            send(0x00); //send cmd(0x00)

            for (uint32_t i = 12; i < 24; i++) {
                send(led[i]);
            }
        }
        latch();
    }
    void LedDevice::latch() {
        digitalWrite(pinData, LOW);
        digitalWrite(pinClock, HIGH); digitalWrite(pinClock, LOW);
        digitalWrite(pinClock, HIGH); digitalWrite(pinClock, LOW);
        delayMicroseconds(240);
        digitalWrite(pinData, HIGH); digitalWrite(pinData, LOW);
        digitalWrite(pinData, HIGH); digitalWrite(pinData, LOW);
        digitalWrite(pinData, HIGH); digitalWrite(pinData, LOW);
        digitalWrite(pinData, HIGH); digitalWrite(pinData, LOW);
        delayMicroseconds(1);
        digitalWrite(pinClock, HIGH);
        digitalWrite(pinClock, LOW);
    }
}
void Grove_LED_Bar::setGreenToRed(bool greenToRed) {
    reverseShow = greenToRed;
    send();
}

void Grove_LED_Bar::setLevel(float level) {
    level = max(0.0F, min(countOfShows, level));
    level *= 8; // there are 8 (noticable) levels of brightness on each segment

    for (uint32_t i = 0; i < countOfShows; i++) {
        led[i] = (level > 8) ? ~0 :
                 (level > 0) ? ~(~0 << byte(level)) : 0;
        level -= 8;
    };

    for (uint32_t i = countOfShows; i < countOfLed(); i++) {
        led[i] = LED_TURN_OFF;
    }
    send();
}

void Grove_LED_Bar::setLed(uint32_t ledNo, float brightness) {
    ledNo = max(1, min(countOfShows, (int)ledNo));
    brightness = max(0.0F, min(brightness, 1.0F));

    // 8 (noticable) levels of brightness
    // 00000000 darkest
    // 00000011 brighter
    // ........
    // 11111111 brightest
    led[ledNo - 1] = ~(~0 << (uint8_t)(brightness * 8));
    send();
}
void Grove_LED_Bar::toggleLed(uint32_t ledNo) {
    uint32_t i =
        ledNo <= countOfShows ?
        ledNo - 1 :
        countOfShows - 1;
    led[i] = led[i] ? LED_TURN_OFF : LED_FULL_BRIGHTNESS;
    send();
}
void Grove_LED_Bar::setBits(uint32_t value) {
    for (uint32_t i = 0; i < countOfLed(); i++, value >>= 1) {
        led[i] = value & 1 ? LED_FULL_BRIGHTNESS : LED_TURN_OFF;
    }

    send();
}
void Grove_LED_Bar::setLedNum(uint32_t count) {
    countOfShows = count;

    for (uint32_t i = count; i < countOfLed(); i++) {
        led[i] = LED_TURN_OFF;
    }
}
uint32_t Grove_LED_Bar::getBits() {
    uint32_t value = 0;
    for (uint32_t i = 0; i < countOfShows; i++) {
        if (led[i] != LED_TURN_OFF) {
            value |= 1 << i;
        }
    }
    return value;
}