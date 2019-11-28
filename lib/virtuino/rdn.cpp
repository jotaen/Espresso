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

  static volatile uint8_t* setupDigitalOutputPin(uint8_t pin, uint8_t bit) {
    Virtuino::pinModes_[~bit] = OUTPUT;
    return 0;
  }

  static void digitalWriteUnchecked(uint8_t bit, volatile uint8_t* out, uint8_t val) {
    Virtuino::digitalOutputs_[~bit] = val;
  }

  static int digitalReadUnchecked(uint8_t bit, volatile uint8_t* portInputRegister) {
    return Virtuino::digitalInputs_[~bit];
  }

  static void analogReadInit(uint8_t poc) {
    Virtuino::adcFinished_ = millis() + 1;
    Virtuino::adcValue_ = Virtuino::analogInputs_[poc];
  }

  static uint8_t analogPinToPoc(uint8_t pin) {
    return pin;
  }

  static bool analogReadInProgress() {
    return millis() < Virtuino::adcFinished_;
  }

  static int analogReadObtain() {
    return Virtuino::adcValue_;
  }

  static void analogWriteUnchecked(uint8_t bit, volatile uint8_t* out, uint8_t timer, int val) {
    Virtuino::analogOutputs_[~bit] = val;
  }

};

#endif
