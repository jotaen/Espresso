#ifndef __YPS_DIGITALINPUT_H__
#define __YPS_DIGITALINPUT_H__

#include "Device.h"

class DigitalInput: public Device {
public:
  DigitalInput(uint8_t pin)
  : pin(pin)
  {}

  int isHigh() {
    return __yps_internal::_digitalRead(this->pin) == HIGH;
  }

  int isLow() {
    return __yps_internal::_digitalRead(this->pin) == LOW;
  }

  int value() {
    return __yps_internal::_digitalRead(this->pin);
  }

protected:
  void onLoop() {}
  const uint8_t pin;
};

#endif
