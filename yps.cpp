#include <Arduino.h>
#include "yps.h"

Device* Device::rootDevice = 0;

unsigned long yps::millis() {
  return ::millis();
}

int __yps_internal::_digitalRead(uint8_t pin) {
  return ::digitalRead(pin);
}

void __yps_internal::_digitalWrite(uint8_t pin, int val) {
  ::digitalWrite(pin, val);
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

void setup() {
  onSetup();
}

void loop() {
  Device* deviceIt = __yps_internal::_getRootDevice();
  do {
    __yps_internal::_callOnLoop(*deviceIt);
    deviceIt = __yps_internal::_getNextDevice(*deviceIt);
  } while (deviceIt != __yps_internal::_getRootDevice());
}
