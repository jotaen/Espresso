#include <Arduino.h>
#include "yps.h"

Device* Device::rootDevice = 0;

unsigned long yps::millis() {
  return millis();
}

int __yps_internal::_digitalRead(uint8_t pin) {
  return 1;
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

void setup() {}

void loop() {}
