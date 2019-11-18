#ifndef __ESPRESSO_UTILS_H_
#define __ESPRESSO_UTILS_H_

namespace fn {

  typedef bool (*Predicate)();
  typedef void (*Handler)();

  bool alwaysTrue() { return true; }

  bool alwaysFalse() { return false; }

  void noop() {}

  void invoke(Handler h) {
    if (h != 0) {
      h();
    }
  }

}

#endif
