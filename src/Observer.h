#ifndef __ESPRESSO_OBSERVER_H__
#define __ESPRESSO_OBSERVER_H__

#include "Device.h"
#include "util/fn.h"

class Observer: public Device {
public:
  Observer(fn::Predicate p)
  : predicate(p)
  , lastState(false)
  , ontrue(0)
  , onfalse(0)
  , whiletrue(0)
  , whilefalse(0)
  {
    this->lastState = this->predicate();
  }

  void onTrue(fn::Handler h) {
    this->ontrue = h;
  }

  void onFalse(fn::Handler h) {
    this->onfalse = h;
  }

  void whileTrue(fn::Handler h) {
    this->whiletrue = h;
  }

  void whileFalse(fn::Handler h) {
    this->whilefalse = h;
  }

protected:
  void onLoop() override {
    bool currentState = this->predicate();
    bool hasStateChanged = this->lastState != currentState;
    if (hasStateChanged) {
      fn::invoke(currentState ? this->ontrue : this->onfalse);
    }
    fn::invoke(currentState ? this->whiletrue : this->whilefalse);
    this->lastState = currentState;
  }

  bool lastState;
  const fn::Predicate predicate;
  fn::Handler ontrue;
  fn::Handler onfalse;
  fn::Handler whiletrue;
  fn::Handler whilefalse;
};

#endif
