#ifndef __YPS_DIGITALINPUT_H__
#define __YPS_DIGITALINPUT_H__

#include "Device.h"

class DigitalInput: public Device {
public:
  DigitalInput(uint8_t pin)
  : pinNr(pin)
  {}

  int isHigh() {
    return __yps_internal::_digitalRead(this->pinNr) == HIGH;
  }

  int isLow() {
    return __yps_internal::_digitalRead(this->pinNr) == LOW;
  }

  int value() {
    return __yps_internal::_digitalRead(this->pinNr);
  }

  uint8_t pin() {
    return this->pinNr;
  }

protected:
  void onLoop() {}
  const uint8_t pinNr;
};

#endif
