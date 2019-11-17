#ifndef __YPS_OBSERVER_H__
#define __YPS_OBSERVER_H__

#include "Device.h"

class Observer: public Device {

  typedef bool (*Predicate)();
  typedef void (*Handler)();

public:
  Observer(Predicate p)
  : predicate(p)
  , lastState(false)
  , ontrue(0)
  , onfalse(0)
  , whiletrue(0)
  , whilefalse(0)
  {
    this->lastState = this->predicate();
  }

  void onTrue(Handler h) {
    this->ontrue = h;
  }

  void onFalse(Handler h) {
    this->onfalse = h;
  }

  void whileTrue(Handler h) {
    this->whiletrue = h;
  }

  void whileFalse(Handler h) {
    this->whilefalse = h;
  }

protected:
  void onLoop() {
    bool currentState = this->predicate();
    bool hasStateChanged = this->lastState != currentState;
    if (hasStateChanged) {
      invoke(currentState ? this->ontrue : this->onfalse);
    }
    invoke(currentState ? this->whiletrue : this->whilefalse);
    this->lastState = currentState;
  }

  void invoke(Handler h) {
    if (h != 0) {
      h();
    }
  }

  bool lastState;
  Predicate predicate;
  Handler ontrue;
  Handler onfalse;
  Handler whiletrue;
  Handler whilefalse;
};

#endif
