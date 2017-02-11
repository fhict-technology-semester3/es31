#ifndef _TIMER_H
#define  _TIMER_H

#include "Arduino.h"

class Timer {
public:
  Timer (double freq);
  bool Deadline();
private:
  double _freq;
  uint32_t _prevMs;
};

#endif
