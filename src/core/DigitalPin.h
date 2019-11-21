#ifndef __ESPRESSO_DIGITALPIN_H__
#define __ESPRESSO_DIGITALPIN_H__

#include "rdn.h"

#ifdef VIRTUINO
  #define ASSERT( bool_expression, error_message ) \
    if (!bool_expression) { throw error_message; }
#else
  #define ASSERT( bool_expression, error_message ) \
    if (!bool_expression) { logger::error(error_message); exit(1); }
#endif

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
    ASSERT(!pinRegistry[this->pin_-1], "PIN already in use");
    pinRegistry[this->pin_-1] = true;
  }

  ~DigitalPin() {
    pinRegistry[this->pin_-1] = false;
  }

  const uint8_t pin_;

  static bool pinRegistry[64];
};

bool DigitalPin::pinRegistry[64] = {false};

#endif
