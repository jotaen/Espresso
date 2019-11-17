#ifndef __YPS_DIGITALOUTPUT_H__
#define __YPS_DIGITALOUTPUT_H__

class DigitalOutput {
public:
  DigitalOutput(const uint8_t pin)
  : pinNr(pin)
  , value_(0)
  {
    pinMode(this->pinNr, OUTPUT);
  }

  uint8_t pin() {
    return this->pinNr;
  }

  int value() {
    return value_;
  }

  bool isHigh() {
    return value_ == HIGH;
  }

  bool isLow() {
    return value_ == LOW;
  }

  void write(int val) {
    digitalWrite(this->pinNr, val);
    this->value_ = val;
  }

  void toggle() {
    this->write(!this->value());
  }

protected:
  const uint8_t pinNr;
  int value_;
};

#endif
