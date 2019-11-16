#define CATCH_CONFIG_MAIN

#include "src/yps.h"
#include "test.h"
#include "src/Device.test.h"
#include "src/Actor.test.h"
#include "src/Timer.test.h"

unsigned long yps::millis() {
  return World::millis;
}

unsigned long World::millis = 0;
Device* yps::rootDevice;
