#define CATCH_CONFIG_MAIN

#include "test.h"
#include "src/yps.h"
#include "src/Device.spec.h"
#include "src/Actor.spec.h"
#include "src/Timer.spec.h"
#include "src/DigitalInput.spec.h"

unsigned long yps::millis() {
  return World::millis;
}

int yps::digitalRead(uint8_t pin) {
  return World::digitalInputs[pin];
}

Device* yps::rootDevice;
