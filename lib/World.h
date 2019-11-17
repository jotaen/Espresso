#ifndef __YPS_WORLD_H__
#define __YPS_WORLD_H__

#include "../src/core.h"
#include "../src/Device.h"
#include <map>

using namespace __yps_internal;

typedef uint8_t byte;
#define HIGH 0x1
#define LOW  0x0

namespace World {
  unsigned long _millis;
  std::map<uint8_t, int> _digitalInputs;
  std::map<uint8_t, int> _digitalOutputs;

  void reset() {
    _clearRootDevice();
    _millis = 0;
    _digitalInputs.clear();
    _digitalOutputs.clear();
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

  int checkDigitalOutput(uint8_t pin) {
    return _digitalOutputs[pin];
  }

  void settle() {
    loopOnce();
  }
};

/**
 *  Definitions of core functions for test context
 */
unsigned long yps::millis() {
  return World::_millis;
}

int __yps_internal::_digitalRead(uint8_t pin) {
  return World::_digitalInputs[pin];
}

void __yps_internal::_digitalWrite(uint8_t pin, int val) {
  World::_digitalOutputs[pin] = val;
}

Device* __yps_internal::_getRootDevice() {
  return Device::rootDevice;
}

void __yps_internal::_clearRootDevice() {
  Device::rootDevice = 0;
}

Device* __yps_internal::_getNextDevice(Device& d) {
  return d.nextDevice;
}

void __yps_internal::_callOnLoop(Device& d) {
  d.onLoop();
}

/**
 *  Other inialisation
 */
Device* Device::rootDevice = 0;

#endif
