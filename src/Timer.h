#ifndef __YPS_TIMER_H__
#define __YPS_TIMER_H__

#include "yps.h"

class Timer: public Device {
  
  typedef void (*Handler)();

public:
  Timer(Handler h)
  : handler(h)
  , isActive(false)
  , intervalMillis(0)
  {}

  void runMillis(unsigned long interval) {
    intervalMillis = interval;
    nextLoop = yps::millis() + interval;
    isActive = true;
  }

protected:
  void onLoop() {
    if (isActive && yps::millis() >= nextLoop) {
      handler();
      nextLoop += intervalMillis;
    }
  }
  Handler handler;
  bool isActive;
  unsigned long intervalMillis;
  unsigned long nextLoop;
};

#endif
