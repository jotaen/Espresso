#ifndef __YPS_YPS_H__
#define __YPS_YPS_H__

#include "Device.h"

class yps {
public:
  static void reset() {
    yps::rootDevice = 0;
  }

  static Device* rootDevice;
};

#endif
