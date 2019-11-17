#define CATCH_CONFIG_MAIN

#include "test.h"
#include "src/core.h"
#include "src/Device.spec.h"
#include "src/Actor.spec.h"
#include "src/Timer.spec.h"
#include "src/DigitalInput.spec.h"

unsigned long yps::millis() {
  return World::_millis;
}

int __yps_internal::_digitalRead(uint8_t pin) {
  return World::_digitalInputs[pin];
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
