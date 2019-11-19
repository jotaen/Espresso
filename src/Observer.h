#ifndef __ESPRESSO_OBSERVER_H__
#define __ESPRESSO_OBSERVER_H__

#include "core/AutoUpdated.h"
#include "util/fn.h"

class Observer: public AutoUpdated {
public:
  Observer(fn::Predicate p)
  : predicate(p)
  , flags_{true, false, ONCE, ONCE}
  , ontrue(0)
  , onfalse(0)
  {
    this->flags_[LAST_STATE] = this->predicate();
  }

  enum RepeatMode {
    ONCE = false,
    WHILE = true
  };

  void onTrue(fn::Handler h, RepeatMode mode = ONCE) {
    this->ontrue = h;
    this->flags_[ONTRUE_MODE] = mode;
  }

  void onFalse(fn::Handler h, RepeatMode mode = ONCE) {
    this->onfalse = h;
    this->flags_[ONFALSE_MODE] = mode;
  }

protected:
  void onLoop() override {
    const bool isTrue = this->predicate();
    const bool hasStateChanged = this->flags_[LAST_STATE] != isTrue;
    const bool isOnceMode = (this->flags_[isTrue ? ONTRUE_MODE : ONFALSE_MODE] == ONCE);
    if (isOnceMode && !hasStateChanged) {
      return;
    }
    fn::invoke(isTrue ? this->ontrue : this->onfalse);
    this->flags_[LAST_STATE] = isTrue;
  }

  enum Flags { ACTIVE, LAST_STATE, ONTRUE_MODE, ONFALSE_MODE };
  bool flags_[4];
  fn::Predicate predicate;
  fn::Handler ontrue;
  fn::Handler onfalse;
};

#endif
