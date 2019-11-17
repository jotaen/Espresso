#ifndef __YPS_DIGITALINPUT_H__
#define __YPS_DIGITALINPUT_H__

#include "Device.h"

class DigitalInput: public Device {
public:
  DigitalInput(uint8_t pin)
  : pinNr(pin)
  {
    pinMode(this->pinNr, INPUT);
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
  void onLoop() {
    update();
  }
  void update() {
    this->value_ = digitalRead(this->pinNr);
  }
  int value_;
  const uint8_t pinNr;
};

#endif
