#ifndef __YPS_TEST_H__
#define __YPS_TEST_H__

#include "src/Device.h"

/**
 *  Class for simulating and manipulating the state of the external Arduino world.
 */
class World {
public:
  static void reset() {
    millis = 0;
  }

  static void elapseMillis(unsigned long m) {
    const unsigned int target = millis + m;
    while(millis < target) {
      millis += 10;
      loopOnce();
    }
  }

  static void loopOnce() {
    Device* deviceIt = yps::rootDevice;
    do {
      yps::callOnLoop(*deviceIt);
      deviceIt = yps::next(*deviceIt);
    } while (deviceIt != yps::rootDevice);
  }

private:
  friend class yps;
  static unsigned long millis;
};

/**
 *  Call spy for testing purpose
 *  This is one global instance, don’t forget to reset!
 */
namespace callspy {

  struct {
    bool hasBeenCalled;
    int count;
  } reporter;

  void Void() {
    reporter.hasBeenCalled = true;
    reporter.count++;
  }

  void reset() {
    reporter.hasBeenCalled = false;
    reporter.count = 0;
  }

}

#endif
