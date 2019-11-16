#define CATCH_CONFIG_MAIN

#include "src/yps.h"
#include "test.h"
#include "src/Device.spec.h"
#include "src/Actor.spec.h"
#include "src/Timer.spec.h"
#include "src/DigitalInput.spec.h"

unsigned long yps::millis() {
  return World::millis;
}

unsigned long World::millis = 0;
Device* yps::rootDevice;
