#ifndef __ESPRESSO_TIMER_H__
#define __ESPRESSO_TIMER_H__

#include "core/AutoUpdated.h"
#include "util/fn.h"

class Timer: public AutoUpdated {
public:
  Timer()
  : handler_(0)
  , flags_{false}
  , delay_(0)
  {}

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

protected:
  void onLoop() override {
    unsigned long now = millis();
    if (!this->flags_[ACTIVE] || now < this->nextTrigger_) {
      return;
    }
    fn::invoke(this->handler_);
    this->flags_[ACTIVE] = false;
  }

  enum Flags { ACTIVE };
  bool flags_[1];
  unsigned long delay_;
  unsigned long nextTrigger_;
  fn::Handler handler_;
};

#endif
