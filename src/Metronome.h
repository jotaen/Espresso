#ifndef __YPS_METRONOME_H__
#define __YPS_METRONOME_H__

#include "core.h"

class Metronome: public Device {
  
  typedef void (*Handler)();

public:
  Metronome(Handler h)
  : handler(h)
  , active(false)
  , intervalMillis(0)
  , nextLoop(0)
  {}

  void runMillis(unsigned long interval) {
    this->intervalMillis = interval;
    this->nextLoop = yps::millis() + interval;
    this->active = true;
    this->handler();
  }

  void stop() {
    this->active = false;
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
    this->nextLoop += this->intervalMillis;
  }

  Handler handler;
  bool active;
  unsigned long intervalMillis;
  unsigned long nextLoop;
};

#endif
