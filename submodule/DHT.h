#ifndef DHT_H
#define DHT_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

// 8 MHz(ish) AVR ---------------------------------------------------------
#if (F_CPU >= 7400000UL) && (F_CPU <= 9500000UL)
#define COUNT 3
// 16 MHz(ish) AVR --------------------------------------------------------
#elif (F_CPU >= 15400000UL) && (F_CPU <= 19000000L)
#define COUNT 6
// 48MHz SAMD21J18A (Sodaq Explorer)
#elif (F_CPU == 48000000UL)
#define COUNT 18
// 168MHz STM32F405 STM32F407
#elif (F_CPU == 168000000L)
#define COUNT 40
#elif (F_CPU == 80000000L)
#define COUNT 22
#elif (F_CPU == 160000000L)
#define COUNT 36
#else
//#error "CPU SPEED NOT SUPPORTED"
#define COUNT 100
#endif

/* DHT library

MIT license
written by Adafruit Industries
*/

// how many timing transitions we need to keep track of. 2 * number bits + extra
#define MAXTIMINGS 85

#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21

class DHT {
 private:
  uint8_t data[6];
  uint8_t _pin, _type, _count;
  boolean read(void);
  unsigned long _lastreadtime;
  boolean firstreading;

 public:
  DHT(uint8_t pin, uint8_t type, uint8_t count=COUNT);
  void begin(void);
  float readTemperature(bool S=false);
  float convertCtoF(float);
  float readHumidity(void);

};
#endif