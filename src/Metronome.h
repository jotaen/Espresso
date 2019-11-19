#ifndef __ESPRESSO_METRONOME_H__
#define __ESPRESSO_METRONOME_H__

#include "core/AutoUpdated.h"
#include "util/fn.h"

class Metronome: public AutoUpdated {
public:
  Metronome()
  : handler(0)
  , flags{false}
  , intervalMillis(0)
  , nextLoop(0)
  {}

  void onTrigger(fn::Handler h) {
    this->handler = h;
  }

  void runMillis(unsigned long interval) {
    this->intervalMillis = interval;
    this->nextLoop = millis() + interval;
    this->flags[ACTIVE] = true;
    fn::invoke(this->handler);
  }

  void run() {
    runMillis(0);
  }

  void stop() {
    this->flags[ACTIVE] = false;
  }

  bool isActive() {
    return flags[ACTIVE];
  }

protected:
  void onLoop() override {
    if (!this->flags[ACTIVE] || millis() < this->nextLoop) {
      return;
    }
    fn::invoke(this->handler);
    this->nextLoop += this->intervalMillis;
  }

  enum Flags { ACTIVE };
  bool flags[1];
  unsigned long intervalMillis;
  unsigned long nextLoop;
  fn::Handler handler;
};

#endif
