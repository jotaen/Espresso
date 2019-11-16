#ifndef __YPS_DIGITALINPUT_H__
#define __YPS_DIGITALINPUT_H__

#include "../test.h"
#include "Device.h"

class DigitalInput: public Device {
public:
  bool isHigh() {
    return false;
  }

  bool isLow() {
    return true;
  }
protected:
  void onLoop() {}
};

#endif
