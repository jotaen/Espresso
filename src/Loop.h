#ifndef __ESPRESSO_LOOP_H__
#define __ESPRESSO_LOOP_H__

#include "core/AutoUpdated.h"
#include "core/fn.h"

/**
 * A handler that gets called over and over again,
 * similarly to the `loop` function
 */
class Loop: public AutoUpdated {
public:
  /**
   * A callback that is supposed to be invoked on each loop
   * (Doesn’t enable it though, in case object had been disabled before)
   */
  void onTrigger(fn::Handler h) {
    this->handler_ = h;
  }

  /**
   * Suspend callback invocation
   */
  void disable() {
    this->flags_[ACTIVE] = false;
  }

  /**
   * Re-enable callback invocation
   */
  void enable() {
    this->flags_[ACTIVE] = true;
  }

  /**
   * Checks whether object is enabled
   */
  bool isActive() {
    return this->flags_[ACTIVE];
  }

  void update() override {
    if (!this->flags_[ACTIVE]) {
      return;
    }
    fn::invoke(this->handler_);
  }

protected:
  enum Flags { ACTIVE };
  bool flags_[1] = { true };
  fn::Handler handler_ = 0;
};

#endif
