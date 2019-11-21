#ifndef __ESPRESSO_CALLSPY_H__
#define __ESPRESSO_CALLSPY_H__

class CallSpy {
public:
  CallSpy():Void(Void_) { counter_ = 0; }

  bool hasBeenCalled() {
    return counter_ > 0;
  }

  unsigned int counter() {
    return counter_;
  }

  const fn::Handler Void;

private:
  static void Void_() {
    counter_++;
  }
  static unsigned int counter_;
};

unsigned int CallSpy::counter_ = 0;

#endif
