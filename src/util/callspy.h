#ifndef __ESPRESSO_CALLSPY_H__
#define __ESPRESSO_CALLSPY_H__

namespace callspy {
  unsigned int _counter;

  void Void() {
    _counter++;
  }

  void reset() {
    _counter = 0;
  }

  bool hasBeenCalled() {
    return _counter > 0;
  }

  unsigned int counter() {
    return _counter;
  }
}

#endif
