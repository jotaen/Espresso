#ifndef __ESPRESSO_DIGITALOUTPUT_H__
#define __ESPRESSO_DIGITALOUTPUT_H__

class DigitalOutput: public DigitalPin {
public:
  DigitalOutput(uint8_t pin)
  : DigitalPin(pin)
  {
    this->outReg_ = rdn::setupDigitalOutputPin(this->pin_, this->bit_, OUTPUT);
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
    rdn::digitalWriteUnchecked(this->bit_, this->outReg_, val);
    this->value_ = val;
  }

  void toggle() {
    this->write(!this->value());
  }

protected:
  volatile uint8_t* outReg_;
  int value_ = 0;
};

#endif
