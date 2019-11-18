#ifndef __ESPRESSO_DIGITALPIN_H__
#define __ESPRESSO_DIGITALPIN_H__

#include "rdn.h"

class DigitalPin {
public:
  DigitalPin(uint8_t pin, uint8_t mode)
  : pin_(pin)
  , bit_(digitalPinToBitMask(pin))
  , port_(digitalPinToPort(pin))
  {
    if (this->port_ == NOT_A_PIN) {
      #ifdef VIRTUINO_ENVIRONMENT
        throw "Invalid PIN number";
      #else
        exit(1);
      #endif
    }
    rdn::setupPin(this->bit_, this->port_, mode);
  }

  uint8_t pin() {
    return this->pin_;
  }

protected:
  const uint8_t pin_;
  const uint8_t bit_;
  const uint8_t port_;
};
  

#endif
