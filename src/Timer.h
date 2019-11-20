#ifndef __ESPRESSO_TIMER_H__
#define __ESPRESSO_TIMER_H__

#include "core/AutoUpdated.h"
#include "util/fn.h"

class Timer: public AutoUpdated {
public:
  void onTrigger(fn::Handler h) {
    this->handler_ = h;
  }

  void start(unsigned long delayMillis) {
    this->delay_ = delayMillis;
    this->start();
  }

  void start() {
    this->nextTrigger_ = millis() + this->delay_;
    this->flags_[ACTIVE] = true;
  }

  void delay(unsigned long delayMillis) {
    this->nextTrigger_ = this->nextTrigger_ - this->delay_ + delayMillis;
    this->delay_ = delayMillis;
  }

  unsigned long delay() {
    return this->delay_;
  }

  void cancel() {
    this->flags_[ACTIVE] = false;
  }

  bool isActive() {
    return this->flags_[ACTIVE];
  }

  void update() override {
    unsigned long now = millis();
    if (!this->flags_[ACTIVE] || now < this->nextTrigger_) {
      return;
    }
    fn::invoke(this->handler_);
    this->flags_[ACTIVE] = false;
  }

protected:
  enum Flags { ACTIVE };
  bool flags_[1] = {false};
  unsigned long delay_ = 0;
  unsigned long nextTrigger_ = 0;
  fn::Handler handler_ = 0;
};

#endif
