#ifndef __ESPRESSO_LOOP_H__
#define __ESPRESSO_LOOP_H__

#include "core/AutoUpdated.h"
#include "util/fn.h"

class Loop: public AutoUpdated {
public:
  void onTrigger(fn::Handler h) {
    this->handler_ = h;
  }

  void disable() {
    this->flags_[ACTIVE] = false;
  }

  void enable() {
    this->flags_[ACTIVE] = true;
  }

  bool isActive() {
    return this->flags_[ACTIVE];
  }

protected:
  void onLoop() override {
    if (!this->flags_[ACTIVE]) {
      return;
    }
    fn::invoke(this->handler_);
  }

  enum Flags { ACTIVE };
  bool flags_[1] = { true };
  fn::Handler handler_ = 0;
};

#endif