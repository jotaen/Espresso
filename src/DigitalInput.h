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
    this->inReg_ = rdn::setupDigitalInputPin(this->pin_, this->bit_, mode);
  }

  bool isHigh() {
    return value() == HIGH;
  }

  bool isLow() {
    return value() == LOW;
  }

  int value() {
    return rdn::digitalReadUnchecked(this->bit_, this->inReg_);
  }

protected:
  volatile uint8_t* inReg_;
  const uint8_t bit_;
};

#endif
