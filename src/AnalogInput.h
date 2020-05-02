#ifndef __ESPRESSO_ANALOGINPUT_H__
#define __ESPRESSO_ANALOGINPUT_H__

#include "core/AutoUpdated.h"

/**
 * Represents an Analog Input Pin
 */
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

  /**
   * Returns current value in the same way that `analogRead` would do
   * Value is cached and might be behind by some 0.1 milliseconds
   */
  int value() {
    return value_;
  }

  /**
   * Returns configured pin number
   */
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

  /**
   * Returns freshly read value in a blocking fashion
   */
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
