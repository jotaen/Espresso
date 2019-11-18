#ifndef __ESPRESSO_H__
#define __ESPRESSO_H__

#include <Arduino.h>

#include "src/Observer.h"
#include "src/Timer.h"
#include "src/Metronome.h"
#include "src/DigitalInput.h"
#include "src/DigitalOutput.h"

Device* Device::rootDevice = 0;

void onSetup();

void setup() {
  onSetup();
}

void loop() {
  Device* deviceIt = Device::rootDevice;
  if (deviceIt == 0) {
    return;
  }
  do {
    (*deviceIt).onLoop();
    deviceIt = (*deviceIt).nextDevice;
  } while (deviceIt != Device::rootDevice);
}

#endif
