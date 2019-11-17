#ifndef __YPS_METRONOME_H__
#define __YPS_METRONOME_H__

#include "core.h"

class Metronome: public Device {
  
  typedef void (*Handler)();

public:
  Metronome()
  : handler(0)
  , active(false)
  , intervalMillis(0)
  , nextLoop(0)
  {}

  Metronome& onTrigger(Handler h) {
    this->handler = h;
    return *this;
  }

  Metronome& runMillis(unsigned long interval) {
    this->intervalMillis = interval;
    this->nextLoop = yps::millis() + interval;
    this->active = true;
    this->invoke();
    return *this;
  }

  Metronome& run() {
    runMillis(0);
    return *this;
  }

  Metronome& stop() {
    this->active = false;
    return *this;
  }

  bool isActive() {
    return active;
  }

protected:
  void onLoop() {
    if (!this->active || yps::millis() < this->nextLoop) {
      return;
    }
    this->invoke();
    this->nextLoop += this->intervalMillis;
  }

  void invoke() {
    if (this->handler) {
      this->handler();
    }
  }

  Handler handler;
  bool active;
  unsigned long intervalMillis;
  unsigned long nextLoop;
};

#endif
