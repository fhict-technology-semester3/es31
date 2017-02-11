#ifndef _LED_H
#define  _LED_H

#include "Arduino.h"

class Led {
public:
  Led (uint8_t pin, double freq);
  void Blink();
private:
  uint8_t _pin;
  double _freq;
  uint8_t _state;
};

#endif
