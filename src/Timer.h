#ifndef __YPS_TIMER_H__
#define __YPS_TIMER_H__

#include "Device.h"
#include "../lib/fn.h"

class Timer: public Device {
public:
  Timer()
  : handler(0)
  , active(false)
  , trigger(0)
  {}

  void onTrigger(fn::Handler h) {
    this->handler = h;
  }

  void start(unsigned long delayMillis) {
    this->trigger = millis() + delayMillis;
    this->active = true;
  }

  void cancel() {
    this->active = false;
  }

  bool isActive() {
    return this->active;
  }

protected:
  void onLoop() {
    if (!this->active || millis() < this->trigger) {
      return;
    }
    fn::invoke(this->handler);
    this->active = false;
  }

  fn::Handler handler;
  bool active;
  unsigned long trigger;
};

#endif
