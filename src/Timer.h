#ifndef __ESPRESSO_TIMER_H__
#define __ESPRESSO_TIMER_H__

#include "core/AutoUpdated.h"
#include "util/fn.h"

class Timer: public AutoUpdated {
public:
  Timer()
  : handler_(0)
  , isActive_(false)
  , delay_(0)
  , lastTriggered_(0)
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
    this->isActive_ = true;
  }

  void delay(unsigned long delayMillis) {
    this->nextTrigger_ = this->nextTrigger_ - this->delay_ + delayMillis;
    this->delay_ = delayMillis;
  }

  unsigned long delay() {
    return this->delay_;
  }

  void cancel() {
    this->isActive_ = false;
  }

  bool isActive() {
    return this->isActive_;
  }

  unsigned long lastTriggered() {
    return this->lastTriggered_;
  }

protected:
  void onLoop() override {
    unsigned long now = millis();
    if (!this->isActive_ || now < this->nextTrigger_) {
      return;
    }
    fn::invoke(this->handler_);
    this->lastTriggered_ = now;
    this->isActive_ = false;
  }

  fn::Handler handler_;
  bool isActive_;
  unsigned long delay_;
  unsigned long lastTriggered_;
  unsigned long nextTrigger_;
};

#endif
