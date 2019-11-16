#ifndef __YPS_DIGITALINPUT_H__
#define __YPS_DIGITALINPUT_H__

#include "../test.h"
#include "Device.h"

class DigitalInput: public Device {
public:
  DigitalInput(uint8_t pin)
  : pin(pin)
  {}

  int isHigh() {
    return yps::digitalRead(this->pin) == HIGH;
  }

  int isLow() {
    return yps::digitalRead(this->pin) == LOW;
  }

  int value() {
    return yps::digitalRead(this->pin);
  }

protected:
  void onLoop() {}
  const uint8_t pin;
};

#endif
