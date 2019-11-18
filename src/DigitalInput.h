#ifndef __ESPRESSO_DIGITALINPUT_H__
#define __ESPRESSO_DIGITALINPUT_H__

#include "core/DigitalPin.h"

class DigitalInput: public DigitalPin {
public:
  DigitalInput(uint8_t pin, uint8_t mode = INPUT)
  : DigitalPin(pin, (mode == INPUT_PULLUP ? INPUT_PULLUP : INPUT))
  {}

  bool isHigh() {
    return value() == HIGH;
  }

  bool isLow() {
    return value() == LOW;
  }

  int value() {
    return rdn::digitalReadUnchecked(this->bit_, this->port_);
  }
};

#endif
