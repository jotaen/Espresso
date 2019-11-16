#ifndef __YPS_TEST_H__
#define __YPS_TEST_H__

#include "lib/catch.hpp"
#include "src/utils.h"
#include "src/Device.h"
#include <map>

/**
 *  Arduino provided fixtures
 */
#define HIGH 0x1
#define LOW  0x0
typedef uint8_t byte;

/**
 *  Class for simulating and manipulating the state of the external Arduino world.
 */
class World {
public:
  static void reset() {
    yps::rootDevice = 0;
    millis = 0;
    digitalInputs.clear();
  }

  static void elapseMillis(unsigned long m) {
    const unsigned int target = millis + m;
    while(millis < target) {
      millis += 1;
      loopOnce();
    }
  }

  static void setDigitalInput(uint8_t pin, int value) {
    digitalInputs[pin] = value;
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
  static std::map<uint8_t, int> digitalInputs;
};

unsigned long World::millis = 0;
std::map<uint8_t, int> World::digitalInputs;


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
