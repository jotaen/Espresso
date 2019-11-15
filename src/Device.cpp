#include "Device.h"

Device::Device() {
  attach();
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
  if (YPS_ROOT_DEVICE == 0) {
    YPS_ROOT_DEVICE = this;
    nextDevice = this;
    previousDevice = this;
  } else {
    previousDevice = YPS_ROOT_DEVICE->previousDevice;
    YPS_ROOT_DEVICE->previousDevice->nextDevice = this;
    nextDevice = YPS_ROOT_DEVICE;
    YPS_ROOT_DEVICE->previousDevice = this;
  }
}

void Device::detach() {
  if (!isAttached()) {
    return;
  }
  previousDevice->nextDevice = nextDevice;
  nextDevice = 0;
  if (YPS_ROOT_DEVICE == this) {
    YPS_ROOT_DEVICE = 0;
  }
}

Device* Device::next() {
  return nextDevice;
}
