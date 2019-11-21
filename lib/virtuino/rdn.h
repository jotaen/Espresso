#ifndef __RDN_H__
#define __RDN_H__

#include "Virtuino.h"

namespace rdn {

  bool isValidPin(uint8_t pin) {
    return pin != NOT_A_PIN;
  }

  volatile uint8_t* setupDigitalInputPin(uint8_t pin, uint8_t bit, uint8_t mode) {
    Virtuino::pinModes_[bit] = mode;
    return 0;
  }

  volatile uint8_t* setupDigitalOutputPin(uint8_t pin, uint8_t bit, uint8_t mode) {
    Virtuino::pinModes_[bit] = mode;
    return 0;
  }

  void digitalWriteUnchecked(uint8_t bit, volatile uint8_t* out, uint8_t val) {
    Virtuino::digitalOutputs_[bit] = val;
  }

  int digitalReadUnchecked(uint8_t bit, volatile uint8_t* portInputRegister) {
    return Virtuino::digitalInputs_[bit];
  }

  void analogReadInit(uint8_t channel) {
    Virtuino::adcFinished_ = millis() + 1;
    Virtuino::adcValue_ = Virtuino::analogInputs_[channel];
  }

  int analogReadTryObtain() {
    if (millis() < Virtuino::adcFinished_) {
      return -1;
    }
    return Virtuino::adcValue_;
  }

}

#endif
