#ifndef __RDN_H__
#define __RDN_H__

struct rdn {

  static bool isValidPin(uint8_t pin) {
    return pin != NOT_A_PIN;
  }

  static volatile uint8_t* setupDigitalInputPin(uint8_t pin, uint8_t bit, uint8_t mode) {
    Virtuino::pinModes_[~bit] = mode;
    return 0;
  }

  static volatile uint8_t* setupDigitalOutputPin(uint8_t pin, uint8_t bit, uint8_t mode) {
    Virtuino::pinModes_[~bit] = mode;
    return 0;
  }

  static void digitalWriteUnchecked(uint8_t bit, volatile uint8_t* out, uint8_t val) {
    Virtuino::digitalOutputs_[~bit] = val;
  }

  static int digitalReadUnchecked(uint8_t bit, volatile uint8_t* portInputRegister) {
    return Virtuino::digitalInputs_[~bit];
  }

  static void analogReadInit(uint8_t channel) {
    Virtuino::adcFinished_ = millis() + 1;
    Virtuino::adcValue_ = Virtuino::analogInputs_[~channel];
  }

  static int analogReadTryObtain() {
    if (millis() < Virtuino::adcFinished_) {
      return -1;
    }
    return Virtuino::adcValue_;
  }

};

#endif
