#ifndef __YPS_TIMER_H__
#define __YPS_TIMER_H__

#include "core.h"

class Timer: public Device {
  
  typedef void (*Handler)();

public:
  Timer(Handler h)
  : handler(h)
  , isActive(false)
  , isRecurring(false)
  , intervalMillis(0)
  , nextLoop(0)
  {}

  void runMillis(unsigned long interval) {
    this->startNow(interval, true);
  }

  void stop() {
    this->isActive = false;
  }

  void onceMillis(unsigned long interval) {
    this->startNow(interval, false);
  }

protected:
  void onLoop() {
    if (!this->isActive || yps::millis() < this->nextLoop) {
      return;
    }
    this->handler();
    if (this->isRecurring) {
      this->nextLoop += this->intervalMillis;
    } else {
      this->stop();
    }
  }

  void startNow(unsigned long interval, bool isRecurring) {
    this->intervalMillis = interval;
    this->nextLoop = yps::millis() + interval;
    this->isActive = true;
    this->isRecurring = isRecurring;
  }

  Handler handler;
  bool isActive;
  bool isRecurring;
  unsigned long intervalMillis;
  unsigned long nextLoop;
};

#endif
