#ifndef __ESPRESSO_TIMER_H__
#define __ESPRESSO_TIMER_H__

#include "core/AutoUpdated.h"
#include "core/fn.h"

class Timer: public AutoUpdated {
public:
  void onTrigger(fn::Handler h) {
    this->handler_ = h;
  }

  void start(unsigned long delayMillis) {
    this->trigger_ = millis() + delayMillis;
    this->flags_[ACTIVE] = true;
  }

  void cancel() {
    this->flags_[ACTIVE] = false;
  }

  bool isActive() {
    return this->flags_[ACTIVE];
  }

  void update() override {
    if (!this->flags_[ACTIVE] || millis() < this->trigger_) {
      return;
    }
    this->flags_[ACTIVE] = false;
    fn::invoke(this->handler_);
  }

protected:
  enum Flags { ACTIVE };
  bool flags_[1] = {false};
  unsigned long trigger_ = 0;
  fn::Handler handler_ = 0;
};

#endif
