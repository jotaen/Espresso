#ifndef __YPS_ACTOR_H__
#define __YPS_ACTOR_H__

#include "Device.h"

class Actor: public Device {

  typedef bool (*Predicate)();
  typedef void (*Handler)();

public:
  Actor(Predicate p)
  : predicate(p)
  , hasLastState(false)
  , lastState(false)
  , ontrue(0)
  , onfalse(0)
  , whiletrue(0)
  , whilefalse(0)
  {}

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
    if (hasStateChanged(currentState)) {
      invoke(currentState ? this->ontrue : this->onfalse);
    }
    invoke(currentState ? this->whiletrue : this->whilefalse);
    this->lastState = currentState;
    this->hasLastState = true;
  }

  bool hasStateChanged(bool newState) {
    return this->hasLastState && (this->lastState != newState);
  }

  void invoke(Handler h) {
    if (h != 0) {
      h();
    }
  }

  bool hasLastState;
  bool lastState;
  Predicate predicate;
  Handler ontrue;
  Handler onfalse;
  Handler whiletrue;
  Handler whilefalse;
};

#endif
