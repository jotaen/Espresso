#define CATCH_CONFIG_MAIN

#include "test.h"
#include "../src/Device.spec.h"
#include "../src/Actor.spec.h"
#include "../src/Timer.spec.h"
#include "../src/DigitalInput.spec.h"

Device* Device::rootDevice = 0;
