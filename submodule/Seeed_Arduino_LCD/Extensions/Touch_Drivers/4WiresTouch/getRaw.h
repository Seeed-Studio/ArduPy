    int temp_x, temp_y, temp_z = 1;
    int samples[NUMSAMPLES];

    uint8_t i, valid;

    // uint8_t xp_port = digitalPinToPort(_xp);
    // unsigned char yp_port = digitalPinToPort(_yp);
    // unsigned char xm_port = digitalPinToPort(_xm);
    // unsigned char ym_port = digitalPinToPort(_ym);

 #ifdef USE_FAST_PINIO
    unsigned char xp_pin = digitalPinToBitMask(_xp);
    unsigned char yp_pin = digitalPinToBitMask(_yp);
    unsigned char xm_pin = digitalPinToBitMask(_xm);
    unsigned char ym_pin = digitalPinToBitMask(_ym);
    valid = 1;
    pinMode(_yp, INPUT);
    pinMode(_ym, INPUT);

    *portOutputRegister(digitalPinToPort(_yp)) &= ~yp_pin;
    *portOutputRegister(digitalPinToPort(_ym)) &= ~ym_pin;

    pinMode(_xp, OUTPUT);
    pinMode(_xm, OUTPUT);

    *portOutputRegister(digitalPinToPort(_xp)) |= xp_pin;
    *portOutputRegister(digitalPinToPort(_xm)) &= ~xm_pin;
#else
   valid = 1;
   pinMode(_yp, INPUT);
   pinMode(_ym, INPUT);
   digitalWrite(_yp, LOW);
   digitalWrite(_ym, LOW);
   
   pinMode(_xp, OUTPUT);
   digitalWrite(_xp, HIGH);
   pinMode(_xm, OUTPUT);
   digitalWrite(_xm, LOW);
#endif

    for (i=0; i<NUMSAMPLES; i++)
    {
#if AVERAGE
        samples[i] = avr_analog(_yp);
#else
        samples[i] = analogRead(_yp);
#endif

    }

#if !COMP
    if (samples[0] != samples[1]) { valid = 0; }
#else
    int icomp = samples[0]>samples[1]?samples[0]-samples[1]:samples[1] - samples[0];
    if(icomp > COMP)valid = 0;
#endif

    temp_x = (samples[0] + samples[1]);

#ifdef USE_FAST_PINIO
    pinMode(_xp, INPUT);
    pinMode(_xm, INPUT);
    *portOutputRegister(digitalPinToPort(_xp)) &= ~xp_pin;
    *portOutputRegister(digitalPinToPort(_xm)) &= ~xm_pin;

    pinMode(_yp, OUTPUT);
    *portOutputRegister(digitalPinToPort(_yp)) |= yp_pin;
    pinMode(_ym, OUTPUT);
    *portOutputRegister(digitalPinToPort(_ym)) &= ~ym_pin;
#else
   pinMode(_xp, INPUT);
   pinMode(_xm, INPUT);
   digitalWrite(_xp, LOW);
   digitalWrite(_xm, LOW);
   
   pinMode(_yp, OUTPUT);
   digitalWrite(_yp, HIGH);
   pinMode(_ym, OUTPUT);
   digitalWrite(_ym, LOW);
#endif

    for (i=0; i<NUMSAMPLES; i++) {
#if AVERAGE
        samples[i] = avr_analog(_xm);
#else
        samples[i] = analogRead(_xm);
#endif
#if TSDEBUG
        yy[i] = samples[i];
#endif
    }

#if !COMP
    if (samples[0] != samples[1]) { valid = 0; }
#else
    icomp = samples[0]>samples[1]?samples[0]-samples[1]:samples[1] - samples[0];
    if(icomp>COMP)valid = 0;
#endif
    temp_y = (samples[0]+samples[1]);


#ifdef USE_FAST_PINIO
    pinMode(_xp, OUTPUT);
    *portOutputRegister(digitalPinToPort(_xp)) &= ~xp_pin;            // Set X+ to ground
    *portOutputRegister(digitalPinToPort(_ym)) |=  ym_pin;            // Set Y- to VCC
    *portOutputRegister(digitalPinToPort(_yp)) &= ~yp_pin;            // Hi-Z X- and Y+
    pinMode(_yp, INPUT);
#else
    // Set X+ to ground
    pinMode(_xp, OUTPUT);
    digitalWrite(_xp, LOW);
  
    // Set Y- to VCC
    pinMode(_ym, OUTPUT);
    digitalWrite(_ym, HIGH); 
  
    // Hi-Z X- and Y+
    digitalWrite(_xm, LOW);
    pinMode(_xm, INPUT);
    digitalWrite(_yp, LOW);
    pinMode(_yp, INPUT);
#endif

    int z1          = analogRead(_xm);
    int z2          = analogRead(_yp);
    float rtouch    = 0;

    rtouch  = z2;
    rtouch /= z1;
    rtouch -= 1;
    rtouch *= (2046-temp_x)/2;
    rtouch *= RXPLATE;
    rtouch /= 1024;
    temp_z = rtouch;
    if (! valid) {
        temp_z = 0;
    }

    
    

