#ifndef __YPS_TIMER_H__
#define __YPS_TIMER_H__

#include "core.h"

class Timer: public Device {
  
  typedef void (*Handler)();

public:
  Timer(Handler h)
  : handler(h)
  , active(false)
  , recurring(false)
  , intervalMillis(0)
  , nextLoop(0)
  {}

  void runMillis(unsigned long interval) {
    this->startNow(interval, true);
  }

  void stop() {
    this->active = false;
  }

  void onceMillis(unsigned long interval) {
    this->startNow(interval, false);
  }

  bool isActive() {
    return active;
  }

protected:
  void onLoop() {
    if (!this->active || yps::millis() < this->nextLoop) {
      return;
    }
    this->handler();
    if (this->recurring) {
      this->nextLoop += this->intervalMillis;
    } else {
      this->stop();
    }
  }

  void startNow(unsigned long interval, bool isRecurring) {
    this->intervalMillis = interval;
    this->nextLoop = yps::millis() + interval;
    this->active = true;
    this->recurring = isRecurring;
  }

  Handler handler;
  bool active;
  bool recurring;
  unsigned long intervalMillis;
  unsigned long nextLoop;
};

#endif
