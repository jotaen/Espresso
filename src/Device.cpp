#include "Device.h"
#include "yps.h"

Device::Device() {
  attach();
}

Device::~Device() {
  detach();
}

bool Device::isAttached() {
  return nextDevice != 0;
}

void Device::attach(bool status) {
  if (!status) {
    detach();
    return;
  }
  if (isAttached()) {
    return;
  }
  if (yps::rootDevice == 0) {
    yps::rootDevice = this;
    nextDevice = this;
    previousDevice = this;
  } else {
    previousDevice = yps::rootDevice->previousDevice;
    yps::rootDevice->previousDevice->nextDevice = this;
    nextDevice = yps::rootDevice;
    yps::rootDevice->previousDevice = this;
  }
}

void Device::detach() {
  if (!isAttached()) {
    return;
  }
  previousDevice->nextDevice = nextDevice;
  nextDevice = 0;
  if (yps::rootDevice == this) {
    yps::rootDevice = 0;
  }
}

Device* Device::next() {
  return nextDevice;
}
