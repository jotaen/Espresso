#ifndef __YPS_DEVICE_H__
#define __YPS_DEVICE_H__

#include "yps.h"

using namespace __yps_internal;

class Device {
public:
  Device() {
    if (rootDevice == 0) {
      rootDevice = this;
      this->nextDevice = this;
      this->previousDevice = this;
    } else {
      this->previousDevice = rootDevice->previousDevice;
      rootDevice->previousDevice->nextDevice = this;
      this->nextDevice = rootDevice;
      rootDevice->previousDevice = this;
    }
  }

  ~Device() {
    this->previousDevice->nextDevice = nextDevice;
    this->nextDevice = 0;
    if (rootDevice == this) {
      rootDevice = 0;
    }
  }

protected:
  friend Device* __yps_internal::_getRootDevice();
  friend Device* __yps_internal::_getNextDevice(Device& d);
  friend void __yps_internal::_callOnLoop(Device& d);
  friend void __yps_internal::_clearRootDevice();

  virtual void onLoop() = 0;
  static Device* rootDevice;
  Device* nextDevice = 0;
  Device* previousDevice = 0;
};

Device* Device::rootDevice = 0;

#endif
