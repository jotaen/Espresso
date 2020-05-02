#ifndef __ESPRESSO_TIMER_H__
#define __ESPRESSO_TIMER_H__

#include "core/AutoUpdated.h"
#include "core/fn.h"

/**
 * Recurringly trigger or schedule a task.
 * Doesn’t guarantee exact timing, but the callback at least won’t
 * be invoked *before* the time has elapsed.
 */
class Timer: public AutoUpdated {
public:

  /**
   * The handler function to be invoked
   */
  void onTrigger(fn::Handler h) {
    this->handler_ = h;
  }

  enum StartOption { START_NOW = 0, START_DELAYED = 1 };
  /**
   * Activate timer. Either start with first invocation right
   * away (`START_NOW`, default) or on next tick (`START_DELAYED`)
   */
  void run(unsigned long interval, StartOption sb = START_NOW) {
    this->start(interval, sb, true);
  }

  /**
   * Triggers callback one time after delay has elapsed
   */
  void runOnce(unsigned long delay) {
    this->start(delay, 1, false);
  }

  /**
   * Stops timer. Safe to call at any time.
   */
  void stop() {
    this->flags_[ACTIVE] = false;
  }

  /**
   * Checks whether object is active.
   */
  bool isActive() {
    return this->flags_[ACTIVE];
  }

  /**
   * Returns currently configured interval
   */
  unsigned long interval() {
    return this->interval_;
  }

  /**
   * Sets a new interval.
   * Applies change after the fact (as if it happened on the last tick)
   */
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

  void start(unsigned long interval, unsigned short firstTriggerOffset, bool isInLoopMode) {
    this->interval_ = interval;
    this->nextTrigger_ = firstTriggerOffset * (millis() + interval);
    this->flags_[ACTIVE] = true;
    this->flags_[LOOP_MODE] = isInLoopMode;
  }
};

#endif
