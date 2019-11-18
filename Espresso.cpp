#include "Espresso.h"

Device* Device::rootDevice = 0;

void setup() {
  onSetup();
}

void loop() {
  Device::loopOnce();
}
