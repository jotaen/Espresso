#include "Device.h"
#include "core.h"

Device::Device() {
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

Device::~Device() {
  previousDevice->nextDevice = nextDevice;
  nextDevice = 0;
  if (_core::rootDevice == this) {
    _core::rootDevice = 0;
  }
}
