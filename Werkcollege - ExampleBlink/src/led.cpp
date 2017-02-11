#include "led.h"
#include "timer.h"

Timer* _t;

  Led::Led (uint8_t pin, double freq) {
    _pin = pin;
    _freq = freq;
    _state = false;
    pinMode(_pin, OUTPUT);
    _t = new Timer(_freq);
  }

  void Led::Blink(){
    if(_t->Deadline()) {
      _state = !_state;
      digitalWrite(_pin, _state);
    }
  }
