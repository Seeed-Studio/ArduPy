#if defined(__SAMD21G18A__)
//
#else
#define USE_FAST_PINIO
#endif

#if defined(KENDRYTE_K210) || defined(ARDUINO_ARCH_SAMD)
  #include <avr/pgmspace.h>
#else
  #include <pgmspace.h>
#endif

#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM A0   // can be a digital pin, this is A0 
#define XP A3   // can be a digital pin, this is A3 

#define NUMSAMPLES 2		// sample number
#define COMP       5
#define AVERAGE    1
#define RXPLATE    300

unsigned char _yp = YP;
unsigned char _xm = XM;
unsigned char _ym = YM;
unsigned char _xp = XP;

#ifdef AVERAGE
#define AVERAGETIME 3
int avr_analog(int adpin)
{
    int sum = 0;
    int max = 0;
    int min = 1024;
    for(int i = 0; i<AVERAGETIME; i++)
    {
        int tmp = analogRead(adpin);
        if(tmp > max)max = tmp;
        if(tmp < min)min = tmp;
        sum += tmp;
        //   sum+=analogRead(adpin);
    }
    return (sum-min-max)/(AVERAGETIME-2);

}

#endif