#ifndef __ESPRESSO_DIGITALINPUT_H__
#define __ESPRESSO_DIGITALINPUT_H__

#include "core/DigitalPin.h"

class DigitalInput: public DigitalPin {
public:
  DigitalInput(uint8_t pin, uint8_t mode = INPUT)
  : DigitalPin(pin)
  , bit_(digitalPinToBitMask(pin))
  {
    ASSERT((mode == INPUT || mode == INPUT_PULLUP), "Invalid mode");

    uint8_t port = digitalPinToPort(pin);
    this->portInputRegister_ = portInputRegister(port);
    rdn::pinModeUnchecked(this->bit_, port, mode);
    
    // Call “regular” digitalRead to ensure PWM is turned Off
    _BLACKLISTED_digitalRead_(this->pin_);
  }

  bool isHigh() {
    return value() == HIGH;
  }

  bool isLow() {
    return value() == LOW;
  }

  int value() {
    return rdn::digitalReadUnchecked(this->bit_, this->portInputRegister_);
  }

protected:
  volatile uint8_t* portInputRegister_;
  const uint8_t bit_;
};

#endif
