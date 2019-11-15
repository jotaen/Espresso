#ifndef __YPS_CORE_H__
#define __YPS_CORE_H__

#include "Device.h"

class _core {
public:
  static void reset() {
    _core::rootDevice = 0;
  }

  static Device* next(Device& d) {
    return d.nextDevice;
  }

  static Device* rootDevice;
};

#endif
