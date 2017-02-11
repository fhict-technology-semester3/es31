#include "timer.h"
#include "Arduino.h"

Timer::Timer(double freq) {
  _freq = freq;
  _prevMs = 0;
}

bool Timer::Deadline() {
  unsigned long _freqToMs = ((1 / _freq) * 1000);
  if ((millis() - _prevMs) >= _freqToMs ) {
    _prevMs = millis();
    return true;
  }
  return false;
}
