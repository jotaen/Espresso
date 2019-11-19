#ifndef __RDN_H__
#define __RDN_H__

#include "Virtuino.h"

namespace rdn {

  bool isValidPin(uint8_t pin) {
    return pin != NOT_A_PIN;
  }

  volatile uint8_t* setupDigitalInputPin(uint8_t pin, uint8_t bit, uint8_t mode) {
    Virtuino::__pinModes[bit] = mode;
    return 0;
  }

  volatile uint8_t* setupDigitalOutputPin(uint8_t pin, uint8_t bit, uint8_t mode) {
    Virtuino::__pinModes[bit] = mode;
    return 0;
  }

  void digitalWriteUnchecked(uint8_t bit, volatile uint8_t* out, uint8_t val) {
    Virtuino::__digitalOutputs[bit] = val;
  }

  int digitalReadUnchecked(uint8_t bit, volatile uint8_t* portInputRegister) {
    return Virtuino::__digitalInputs[bit];
  }

}

#endif
