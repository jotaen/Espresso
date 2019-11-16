#define CATCH_CONFIG_MAIN

#include "src/yps.h"
#include "src/Device.test.h"
#include "src/Actor.test.h"
#include "src/Timer.test.h"

void yps::reset() {
  rootDevice = 0;
}

Device* yps::next(Device& d) {
  return d.nextDevice;
}

void yps::callOnLoop(Device& d) {
  d.onLoop();
}

Device* yps::rootDevice;
