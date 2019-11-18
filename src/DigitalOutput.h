#ifndef __ESPRESSO_DIGITALOUTPUT_H__
#define __ESPRESSO_DIGITALOUTPUT_H__

class DigitalOutput: public DigitalPin {
public:
  DigitalOutput(uint8_t pin)
  : DigitalPin(pin, OUTPUT)
  , value_(0)
  {}

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
    rdn::digitalWriteUnchecked(this->bit_, this->port_, val);
    this->value_ = val;
  }

  void toggle() {
    this->write(!this->value());
  }

protected:
  int value_;
};

#endif
