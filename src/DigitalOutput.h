#ifndef __YPS_DIGITALOUTPUT_H__
#define __YPS_DIGITALOUTPUT_H__

class DigitalOutput {
public:
  DigitalOutput(uint8_t pin)
  : pinNr(pin)
  , value(0)
  {}

  uint8_t pin() {
    return this->pinNr;
  }

  int get() {
    return value;
  }

  bool isHigh() {
    return value == HIGH;
  }

  bool isLow() {
    return value == LOW;
  }

  void set(int val) {
    __yps_internal::_digitalWrite(this->pinNr, val);
    this->value = val;
  }

protected:
  const uint8_t pinNr;
  int value;
};

#endif
