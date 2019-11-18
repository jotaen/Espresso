#ifndef __YPS_DIGITALINPUT_H__
#define __YPS_DIGITALINPUT_H__

#include "Device.h"

class DigitalInput: public Device {
public:
  DigitalInput(uint8_t pin, uint8_t mode = INPUT)
  : pinNr(pin)
  {
    pinMode(this->pinNr, (mode == INPUT_PULLUP ? INPUT_PULLUP : INPUT));
    update();
  }

  int isHigh() {
    return value_ == HIGH;
  }

  int isLow() {
    return value_ == LOW;
  }

  int value() {
    return value_;
  }

  uint8_t pin() {
    return this->pinNr;
  }

protected:
  void onLoop() override {
    update();
  }
  void update() {
    this->value_ = digitalRead(this->pinNr);
  }
  const uint8_t pinNr;
  int value_;
};

#endif
