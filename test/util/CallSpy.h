#ifndef __ESPRESSO_CALLSPY_H__
#define __ESPRESSO_CALLSPY_H__

class CallSpy {
public:
  CallSpy()
  : Void(Void_)
  , Bool(Bool_)
  { counter_ = 0; }

  bool hasBeenCalled() {
    return counter_ > 0;
  }

  unsigned int counter() {
    return counter_;
  }

  const fn::Handler Void;
  const fn::BoolHandler Bool;

private:
  static void Void_() {
    counter_++;
  }
  static void Bool_(bool) {
    counter_++;
  }
  static unsigned int counter_;
};

unsigned int CallSpy::counter_ = 0;

#endif
