#ifndef __ESPRESSO_METRONOME_H__
#define __ESPRESSO_METRONOME_H__

#include "core/AutoUpdated.h"
#include "util/fn.h"

class Metronome: public AutoUpdated {
public:
  void onTrigger(fn::Handler h) {
    this->handler_ = h;
  }

  void run(unsigned long interval) {
    this->interval_ = interval;
    this->nextLoop_ = millis() + interval;
    this->flags_[ACTIVE] = true;
    fn::invoke(this->handler_);
  }

  void stop() {
    this->flags_[ACTIVE] = false;
  }

  bool isActive() {
    return this->flags_[ACTIVE];
  }

  void update() override {
    if (!this->flags_[ACTIVE] || millis() < this->nextLoop_) {
      return;
    }
    fn::invoke(this->handler_);
    this->nextLoop_ += this->interval_;
  }

protected:
  enum Flags { ACTIVE };
  bool flags_[1] = { false };
  unsigned long interval_ = 0;
  unsigned long nextLoop_ = 0;
  fn::Handler handler_ = 0;
};

#endif
