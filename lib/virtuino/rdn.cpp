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

  static uint8_t analogPinToPoc(uint8_t pin) {
    return pin;
  }

  static bool isAnalogReadInProgress() {
    return false;
  }

  static void analogReadInit(uint8_t poc) {
    if (isAnalogReadInProgress()) {
      throw std::runtime_error("Cannot start analog read while ADC is occupied");
    }
    Virtuino::adcValue_ = Virtuino::analogInputs_[poc];
  }

  static int analogReadGetLastValue() {
    return Virtuino::adcValue_;
  }

  static void analogWriteUnchecked(uint8_t bit, volatile uint8_t* out, uint8_t timer, int val) {
    Virtuino::analogOutputs_[~bit] = val;
  }

  static bool checkForSerialEvent(uint8_t serialPort) {
    return !Virtuino::serialData_[serialPort].empty();
  }

};

#endif
