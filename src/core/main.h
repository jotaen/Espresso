#ifndef __ESPRESSO_MAIN_H__
#define __ESPRESSO_MAIN_H__

Device* Device::rootDevice = 0;

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
