#ifndef __YPS_TEST_H__
#define __YPS_TEST_H__

#include "lib/catch.hpp"
#include "src/core.h"
#include "src/utils.h"
#include "src/Device.h"
#include <map>

using namespace __yps_internal;

/**
 *  Arduino provided fixtures
 */
#define HIGH 0x1
#define LOW  0x0
typedef uint8_t byte;

/**
 *  Class for simulating and manipulating the state of the external Arduino world.
 */
namespace World {
  unsigned long _millis;
  std::map<uint8_t, int> _digitalInputs;

  void reset() {
    _clearRootDevice();
    _millis = 0;
    _digitalInputs.clear();
  }

  void loopOnce() {
    Device* deviceIt = _getRootDevice();
    do {
      _callOnLoop(*deviceIt);
      deviceIt = _getNextDevice(*deviceIt);
    } while (deviceIt != _getRootDevice());
  }

  void elapseMillis(unsigned long m) {
    const unsigned int target = _millis + m;
    while(_millis < target) {
      _millis += 1;
      loopOnce();
    }
  }

  void setDigitalInput(uint8_t pin, int value) {
    _digitalInputs[pin] = value;
  }

  void settle() {
    loopOnce();
  }
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
