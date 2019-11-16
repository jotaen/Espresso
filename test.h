#ifndef __YPS_TEST_H__
#define __YPS_TEST_H__

#include "src/Device.h"

/**
 *  Class for simulating and manipulating the state of the external Arduino world.
 */
class World {
public:
  static void reset() {
    yps::rootDevice = 0;
    millis = 0;
  }

  static void elapseMillis(unsigned long m) {
    const unsigned int target = millis + m;
    while(millis < target) {
      millis += 7;
      loopOnce();
    }
  }

  static void settle() {
    loopOnce();
  }

  static void loopOnce() {
    Device* deviceIt = yps::rootDevice;
    do {
      (*deviceIt).onLoop();
      deviceIt = (*deviceIt).nextDevice;
    } while (deviceIt != yps::rootDevice);
  }

  static Device* getNext(Device& d) {
    return d.nextDevice;
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
