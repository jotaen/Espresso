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
  {
    ASSERT(rdn::isValidPin(this->pin_), "Invalid PIN number");
  }

  const uint8_t pin_;
};

#endif
