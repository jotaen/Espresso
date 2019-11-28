#ifndef __ESPRESSO_TIMER_H__
#define __ESPRESSO_TIMER_H__

#include "core/AutoUpdated.h"
#include "core/fn.h"

class Timer: public AutoUpdated {
public:
  void onTrigger(fn::Handler h) {
    this->handler_ = h;
  }

  enum StartBehaviour { START_NOW, START_DELAYED };
  void run(unsigned long interval, StartBehaviour sb = START_NOW) {
    this->start(interval, true);
    if (sb == START_NOW) {
      fn::invoke(this->handler_);
    }
  }

  void runOnce(unsigned long delay) {
    this->start(delay, false);
  }

  void stop() {
    this->flags_[ACTIVE] = false;
  }

  bool isActive() {
    return this->flags_[ACTIVE];
  }

  unsigned long interval() {
    return this->interval_;
  }

  void interval(unsigned long newInterval) {
    this->nextTrigger_ = (this->nextTrigger_ - this->interval_) + newInterval;
    this->interval_ = newInterval;
  }

  void update() override {
    if (!this->flags_[ACTIVE] || millis() < this->nextTrigger_) {
      return;
    }
    if (this->flags_[LOOP_MODE]) {
      this->nextTrigger_ += this->interval_;
    } else {
      this->flags_[ACTIVE] = false;
    }
    fn::invoke(this->handler_);
  }

protected:
  enum Flags { ACTIVE, LOOP_MODE };
  bool flags_[2] = { false };
  unsigned long nextTrigger_ = 0;
  unsigned long interval_ = 0;
  fn::Handler handler_ = 0;

  void start(unsigned long interval, bool isInLoopMode) {
    this->interval_ = interval;
    this->nextTrigger_ = millis() + interval;
    this->flags_[ACTIVE] = true;
    this->flags_[LOOP_MODE] = isInLoopMode;
  }
};

#endif
