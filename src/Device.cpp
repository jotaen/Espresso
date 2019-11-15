#include "Device.h"
#include "core.h"

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
  if (_core::rootDevice == 0) {
    _core::rootDevice = this;
    nextDevice = this;
    previousDevice = this;
  } else {
    previousDevice = _core::rootDevice->previousDevice;
    _core::rootDevice->previousDevice->nextDevice = this;
    nextDevice = _core::rootDevice;
    _core::rootDevice->previousDevice = this;
  }
}

void Device::detach() {
  if (!isAttached()) {
    return;
  }
  previousDevice->nextDevice = nextDevice;
  nextDevice = 0;
  if (_core::rootDevice == this) {
    _core::rootDevice = 0;
  }
}
