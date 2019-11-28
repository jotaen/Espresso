#ifndef __ESPRESSO_ANALOGINPUT_H__
#define __ESPRESSO_ANALOGINPUT_H__

#include "core/AutoUpdated.h"

class AnalogInput: public AutoUpdated {
public:
  AnalogInput(uint8_t pin)
  : pin_(pin)
  , poc_(rdn::analogPinToPoc(pin))
  {}

  int value() {
    return value_;
  }

  int pin() {
    return this->pin_;
  }

  void update() {
    if (adcAcquiredPin == FREE) {
      startRead();
      // We can return here already, as the ADC takes ~100μs, so it
      // won’t be finished anytime soon.
      return;
    }
    if (adcAcquiredPin == this->pin_) {
      tryReadFromADC();
    }
  }

  int valueBlocking() {
    do {
      this->update();
    } while(adcAcquiredPin != FREE);
    return this->value_;
  }

protected:
  inline void startRead() {
    rdn::analogReadInit(this->poc_);
    adcAcquiredPin = this->pin_;
  }

  inline void tryReadFromADC() {
    if (rdn::analogReadInProgress()) {
      return;
    }
    this->value_ = rdn::analogReadObtain();
    adcAcquiredPin = FREE;
  }

  int value_ = 0;
  uint8_t pin_ = 0;
  uint8_t poc_ = 0;
  static const uint8_t FREE = 255;
  static uint8_t adcAcquiredPin;
};

uint8_t AnalogInput::adcAcquiredPin = AnalogInput::FREE;

#endif
