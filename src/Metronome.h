#ifndef __YPS_METRONOME_H__
#define __YPS_METRONOME_H__

#include "Device.h"
#include "../lib/fn.h"

class Metronome: public Device {
public:
  Metronome()
  : handler(0)
  , active(false)
  , intervalMillis(0)
  , nextLoop(0)
  {}

  void onTrigger(fn::Handler h) {
    this->handler = h;
  }

  void runMillis(unsigned long interval) {
    this->intervalMillis = interval;
    this->nextLoop = millis() + interval;
    this->active = true;
    fn::invoke(this->handler);
  }

  void run() {
    runMillis(0);
  }

  void stop() {
    this->active = false;
  }

  bool isActive() {
    return active;
  }

protected:
  void onLoop() {
    if (!this->active || millis() < this->nextLoop) {
      return;
    }
    fn::invoke(this->handler);
    this->nextLoop += this->intervalMillis;
  }

  fn::Handler handler;
  bool active;
  unsigned long intervalMillis;
  unsigned long nextLoop;
};

#endif
