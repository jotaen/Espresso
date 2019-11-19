#ifndef __ESPRESSO_DIGITALPIN_H__
#define __ESPRESSO_DIGITALPIN_H__

#include "rdn.h"

class DigitalPin {
public:
  uint8_t pin() {
    return this->pin_;
  }

protected:
  DigitalPin(uint8_t pin)
  : pin_(pin)
  , bit_(digitalPinToBitMask(pin))
  {
    ASSERT(rdn::isValidPin(this->pin_), "Invalid PIN number");
    ASSERT(!pinRegistry[this->pin_-1], "PIN already in use");
    pinRegistry[this->pin_-1] = true;
  }

  ~DigitalPin() {
    pinRegistry[this->pin_-1] = false;
  }

  const uint8_t pin_;
  const uint8_t bit_;

  static bool pinRegistry[64];
};

#endif
