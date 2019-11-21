#ifndef __ESPRESSO_ANALOGINPUT_H__
#define __ESPRESSO_ANALOGINPUT_H__

#include "core/AutoUpdated.h"

class AnalogInput: public AutoUpdated {
public:
  AnalogInput(uint8_t pin)
  : pin_(pin)
  , channel_(analogPinToChannel(pin))
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

protected:
  inline void startRead() {
    rdn::analogReadInit(this->channel_);
    adcAcquiredPin = this->pin_;
  }

  inline void tryReadFromADC() {
    int newValue = rdn::analogReadTryObtain();
    if (newValue == IN_PROGRESS) {
      return;
    }
    this->value_ = newValue;
    adcAcquiredPin = FREE;
  }

  int value_ = 0;
  uint8_t pin_ = 0;
  uint8_t channel_ = 0;
  static const int IN_PROGRESS = -1;
  static const uint8_t FREE = 255;
  static uint8_t adcAcquiredPin;
};

uint8_t AnalogInput::adcAcquiredPin = AnalogInput::FREE;

#endif
