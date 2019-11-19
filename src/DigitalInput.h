#ifndef __ESPRESSO_DIGITALINPUT_H__
#define __ESPRESSO_DIGITALINPUT_H__

#include "core/DigitalPin.h"

class DigitalInput: public DigitalPin {
public:
  DigitalInput(uint8_t pin, uint8_t mode = INPUT)
  : DigitalPin(pin)
  , bit_(digitalPinToBitMask(pin))
  , port_(digitalPinToPort(pin))
  {
    ASSERT((mode == INPUT || mode == INPUT_PULLUP), "Invalid mode");
    rdn::pinModeUnchecked(this->bit_, this->port_, mode);
  }

  bool isHigh() {
    return value() == HIGH;
  }

  bool isLow() {
    return value() == LOW;
  }

  int value() {
    return rdn::digitalReadUnchecked(this->bit_, this->port_);
  }

protected:
  const uint8_t bit_;
  const uint8_t port_;
};

#endif
