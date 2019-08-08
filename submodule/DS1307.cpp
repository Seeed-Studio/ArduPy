/*
 * DS1307.h
 * library for Seeed RTC module
 *
 * Copyright (c) 2013 seeed technology inc.
 * Author        :   FrankieChu 
 * Create Time   :   Jan 2013
 * Change Log    :
 *
 * The MIT License (MIT)
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

#include <Wire.h>
#include "DS1307.h"

uint8_t DS1307::decToBcd(uint8_t val)
{
    return ( (val/10*16) + (val%10) );
}

//Convert binary coded decimal to normal decimal numbers
uint8_t DS1307::bcdToDec(uint8_t val)
{
    return ( (val/16*10) + (val%16) );
}

void DS1307::begin()
{
    Wire.begin();
}
/*Function: The clock timing will start */
void DS1307::startClock(void)        // set the ClockHalt bit low to start the rtc
{
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write((uint8_t)0x00);                      // Register 0x00 holds the oscillator start/stop bit
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 1);
  second = Wire.read() & 0x7f;       // save actual seconds and AND sec with bit 7 (sart/stop bit) = clock started
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write((uint8_t)0x00);
  Wire.write((uint8_t)second);                    // write seconds back and start the clock
  Wire.endTransmission();
}
/*Function: The clock timing will stop */
void DS1307::stopClock(void)         // set the ClockHalt bit high to stop the rtc
{
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write((uint8_t)0x00);                      // Register 0x00 holds the oscillator start/stop bit
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 1);
  second = Wire.read() | 0x80;       // save actual seconds and OR sec with bit 7 (sart/stop bit) = clock stopped
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write((uint8_t)0x00);
  Wire.write((uint8_t)second);                    // write seconds back and stop the clock
  Wire.endTransmission();
}
/****************************************************************/
/*Function: Read time and date from RTC */
void DS1307::getTime()
{
    // Reset the register pointer
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();  
    Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
    // A few of these need masks because certain bits are control bits
    second     = bcdToDec(Wire.read() & 0x7f);
    minute     = bcdToDec(Wire.read());
    hour       = bcdToDec(Wire.read() & 0x3f);// Need to change this if 12 hour am/pm
    dayOfWeek  = bcdToDec(Wire.read());
    dayOfMonth = bcdToDec(Wire.read());
    month      = bcdToDec(Wire.read());
    year       = bcdToDec(Wire.read());
}
/*******************************************************************/
/*Frunction: Write the time that includes the date to the RTC chip */
void DS1307::setTime()
{
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.write(decToBcd(second));// 0 to bit 7 starts the clock
    Wire.write(decToBcd(minute));
    Wire.write(decToBcd(hour));  // If you want 12 hour am/pm you need to set bit 6 
    Wire.write(decToBcd(dayOfWeek));
    Wire.write(decToBcd(dayOfMonth));
    Wire.write(decToBcd(month));
    Wire.write(decToBcd(year));
    Wire.endTransmission();
}
void DS1307::fillByHMS(uint8_t _hour, uint8_t _minute, uint8_t _second)
{
    // assign variables
    hour = _hour;
    minute = _minute;
    second = _second;
}
void DS1307::fillByYMD(uint16_t _year, uint8_t _month, uint8_t _day)
{
    year = _year-2000;
    month = _month;
    dayOfMonth = _day;
}
void DS1307::fillDayOfWeek(uint8_t _dow)
{
    dayOfWeek = _dow;
}

