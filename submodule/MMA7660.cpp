/*
 * MMA7760.h
 * Library for accelerometer_MMA7760
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

#include <Arduino.h>
#include <Wire.h>
#include "MMA7660.h"

#define MMA7660TIMEOUT  500         // us
/*Function: Write a byte to the register of the MMA7660*/
void MMA7660::write(uint8_t _register, uint8_t _data) {
    Wire.begin();
    Wire.beginTransmission(MMA7660_ADDR);
    Wire.write(_register);
    Wire.write(_data);
    Wire.endTransmission();
}

/*Function: Read a byte from the regitster of the MMA7660*/
uint8_t MMA7660::read(uint8_t _register) {
    uint8_t data_read;
    Wire.begin();
    Wire.beginTransmission(MMA7660_ADDR);
    Wire.write(_register);
    Wire.endTransmission();
    Wire.beginTransmission(MMA7660_ADDR);
    Wire.requestFrom(MMA7660_ADDR,1);
    while(Wire.available())
    {
        data_read = Wire.read();
    }
    Wire.endTransmission();
    return data_read;
}

// populate lookup table based on the MMA7660 datasheet at http://www.farnell.com/datasheets/1670762.pdf
void MMA7660::initAccelTable() {
    int i;
    float val, valZ;

    for (i = 0, val = 0; i < 32; i++) {
        accLookup[i].g = val;
        val += 0.047;
    }

    for (i = 63, val = -0.047; i > 31; i--) {
        accLookup[i].g = val;
        val -= 0.047;
    }

    for (i = 0, val = 0, valZ = 90; i < 22; i++) {
        accLookup[i].xyAngle = val;
        accLookup[i].zAngle = valZ;

        val += 2.69;
        valZ -= 2.69;
    }

    for (i = 63, val = -2.69, valZ = -87.31; i > 42; i--) {
        accLookup[i].xyAngle = val;
        accLookup[i].zAngle = valZ;

        val -= 2.69;
        valZ += 2.69;
    }

    for (i = 22; i < 43; i++) {
        accLookup[i].xyAngle = 255;
        accLookup[i].zAngle = 255;
    }
}

void MMA7660::init()
{
    initAccelTable();
    setMode(MMA7660_STAND_BY);
    setSampleRate(AUTO_SLEEP_32);
    setMode(MMA7660_ACTIVE);
}

void MMA7660::init(uint8_t interrupts)
{
    initAccelTable();
    setMode(MMA7660_STAND_BY);
    setSampleRate(AUTO_SLEEP_32);
    write(MMA7660_INTSU, interrupts);
    setMode(MMA7660_ACTIVE);
}
void MMA7660::setMode(uint8_t mode) {
    write(MMA7660_MODE,mode);
}
void MMA7660::setSampleRate(uint8_t rate) {
    write(MMA7660_SR,rate);
}

/*Function: Get the contents of the registers in the MMA7660*/
/*          so as to calculate the acceleration.            */
bool MMA7660::getXYZ(int8_t *x,int8_t *y,int8_t *z)
{
    
START:

    unsigned char val[3];
    int count = 0;
    val[0] = val[1] = val[2] = 64;
    while(Wire.available() > 0)
    Wire.read();

    Wire.requestFrom(MMA7660_ADDR,3);

    unsigned long timer_s = micros();

    while(Wire.available())
    {
        if(count < 3)
        {
            while ( val[count] > 63 )  // reload the damn thing it is bad
            {
                val[count] = Wire.read();

                if(micros()-timer_s > MMA7660TIMEOUT)
                {
                    goto START;
                }
            }
        }
        count++;
    }

    *x = ((int8_t)(val[0]<<2))/4;
    *y = ((int8_t)(val[1]<<2))/4;
    *z = ((int8_t)(val[2]<<2))/4;
    
    return 1;
}

bool MMA7660::getAcceleration(float *ax,float *ay,float *az)
{
    int8_t x,y,z;
    if(!getXYZ(&x,&y,&z))return 0;
    *ax = x/21.00;
    *ay = y/21.00;
    *az = z/21.00;
    
    return 1;
}

bool MMA7660::getAcceleration(MMA7660_ACC_DATA *data) {
    unsigned char val[3];
    int count;
    bool error;

    unsigned long timer_s = micros();
    do {
        error = false;
        count = 0;

        while(Wire.available() > 0) {
            Wire.read();
        }

        Wire.requestFrom(MMA7660_ADDR, 3);
        while(Wire.available()) {
            if (count < 3) {
                val[count] = Wire.read();
                if (0x40 & val[count] == 0x40) { // alert bit is set, data is garbage and we have to start over.
                    error = true;
                    break;
                }
            }
            count++;
        }
        
        if(micros()-timer_s > MMA7660TIMEOUT)return 0;
    } while (error);

    (*data).x = accLookup[val[0]];
    (*data).y = accLookup[val[1]];
    (*data).z = accLookup[val[2]];
    
    return 1;
}

bool MMA7660::getAllData(MMA7660_DATA *data) {
    int count = 0;
    uint8_t val[11] = {0};

    while (Wire.available() > 0) {
        Wire.read();
    }

    Wire.requestFrom(MMA7660_ADDR, 11);
    while (Wire.available()) {
        if (count < 11) {
            val[count] = Wire.read();
        }
        count++;
    }

    data->X = val[0];
    data->Y = val[1];
    data->Z = val[2];
    data->TILT = val[3];
    data->SRST = val[4];
    data->SPCNT = val[5];
    data->INTSU = val[6];
    data->MODE = val[7];
    data->SR = val[8];
    data->PDET = val[9];
    data->PD = val[10];
    
    return 1;
}
