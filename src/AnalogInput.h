#ifndef __ESPRESSO_ANALOGINPUT_H__
#define __ESPRESSO_ANALOGINPUT_H__

#include "core/AutoUpdated.h"

class AnalogInput: public AutoUpdated {
public:
  AnalogInput(uint8_t pin)
  : pin_(pin)
  , poc_(rdn::analogPinToPoc(pin))
  {}

  ~AnalogInput() {
    if (currentlyReadingPin == this->pin_) {
      currentlyReadingPin = NONE;
    }
  }

  int value() {
    return value_;
  }

  int pin() {
    return this->pin_;
  }

  void update() {
    if (currentlyReadingPin == NONE) {
      rdn::analogReadInit(this->poc_);
      currentlyReadingPin = this->pin_;
      return; // return right away, the next condition won’t be `true` yet
    }
    if (currentlyReadingPin == this->pin_ && !rdn::isAnalogReadInProgress()) {
      this->value_ = rdn::analogReadGetLastValue();
      currentlyReadingPin = NONE;
    }
  }

  int valueBlocking() {
    while (rdn::isAnalogReadInProgress()); // wait for previous analog-reads to finish first
    currentlyReadingPin = NONE; // clear
    do {
      this->update();
    } while (rdn::isAnalogReadInProgress());
    return this->value_;
  }

protected:
  int value_ = 0;
  uint8_t pin_ = 0;
  uint8_t poc_ = 0;
  static const uint8_t NONE = 255;
  static uint8_t currentlyReadingPin;
};

uint8_t AnalogInput::currentlyReadingPin = AnalogInput::NONE;

#endif
