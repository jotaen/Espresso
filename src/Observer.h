#ifndef __ESPRESSO_OBSERVER_H__
#define __ESPRESSO_OBSERVER_H__

#include "core/AutoUpdated.h"
#include "core/fn.h"

class Observer: public AutoUpdated {
public:
  Observer(fn::Predicate p)
  : predicate(p)
  {
    this->flags_[LAST_STATE] = this->predicate();
  }

  enum RepeatMode {
    ONCE = false,
    WHILE = true
  };

  void onTrue(fn::Handler h, RepeatMode mode = ONCE) {
    this->onTrue_ = h;
    this->flags_[ONTRUE_MODE] = mode;
  }

  void onFalse(fn::Handler h, RepeatMode mode = ONCE) {
    this->onFalse_ = h;
    this->flags_[ONFALSE_MODE] = mode;
  }

  void enable() {
    this->flags_[ACTIVE] = true;
  }

  void disable() {
    this->flags_[ACTIVE] = false;
  }

  bool isActive() {
    return this->flags_[ACTIVE];
  }

  void update() override {
    if (!this->flags_[ACTIVE]) {
      return;
    }
    const bool isTrue = this->predicate();
    const bool hasStateChanged = this->flags_[LAST_STATE] != isTrue;
    const bool isOnceMode = (this->flags_[isTrue ? ONTRUE_MODE : ONFALSE_MODE] == ONCE);
    if (!hasStateChanged && isOnceMode) {
      return;
    }
    fn::invoke(isTrue ? this->onTrue_ : this->onFalse_);
    this->flags_[LAST_STATE] = isTrue;
  }

protected:
  enum Flags { ACTIVE, LAST_STATE, ONTRUE_MODE, ONFALSE_MODE };
  bool flags_[4] = {true, false, ONCE, ONCE};
  const fn::Predicate predicate;
  fn::Handler onTrue_ = 0;
  fn::Handler onFalse_ = 0;
};

#endif
