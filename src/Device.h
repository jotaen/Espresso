#ifndef __YPS_DEVICE_H__
#define __YPS_DEVICE_H__

#include "yps.h"

class Device {
public:
  Device() {
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

  ~Device() {
    previousDevice->nextDevice = nextDevice;
    nextDevice = 0;
    if (yps::rootDevice == this) {
      yps::rootDevice = 0;
    }
  }

protected:
  virtual void onLoop() = 0;

private:
  friend class yps;
  Device* nextDevice = 0;
  Device* previousDevice = 0;
};

#endif
