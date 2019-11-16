#define CATCH_CONFIG_MAIN

#include "src/yps.h"
#include "test.h"
#include "src/Device.test.h"
#include "src/Actor.test.h"
#include "src/Timer.test.h"

unsigned long yps::millis() {
  return World::millis;
}

void yps::reset() {
  rootDevice = 0;
}

Device* yps::next(Device& d) {
  return d.nextDevice;
}

void yps::callOnLoop(Device& d) {
  d.onLoop();
}

unsigned long World::millis = 0;
Device* yps::rootDevice;
