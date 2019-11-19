#ifndef __ESPRESSO_DIGITALOUTPUT_H__
#define __ESPRESSO_DIGITALOUTPUT_H__

class DigitalOutput: public DigitalPin {
public:
  DigitalOutput(uint8_t pin)
  : DigitalPin(pin)
  , bit_(digitalPinToBitMask(pin))
  , value_(0)
  {
    const uint8_t port = digitalPinToPort(pin);
    rdn::pinModeUnchecked(this->bit_, port, OUTPUT);
    this->portOutputRegister_ = portOutputRegister(port);

    // Call “regular” digitalWrite to ensure PWM is turned Off
    ::_BLACKLISTED_digitalWrite_(this->pin_, 0);
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
    rdn::digitalWriteUnchecked(this->bit_, this->portOutputRegister_, val);
    this->value_ = val;
  }

  void toggle() {
    this->write(!this->value());
  }

protected:
  const uint8_t bit_;
  volatile uint8_t* portOutputRegister_;
  int value_;
};

#endif
