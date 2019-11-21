#ifndef __ESPRESSO_ANALOGOUTPUT_H__
#define __ESPRESSO_ANALOGOUTPUT_H__

class AnalogOutput: public DigitalPin {
public:
  AnalogOutput(uint8_t pin)
  : DigitalPin(pin)
  , timer_(digitalPinToTimer(pin))
  {
    // Warning: The following assertion is not unit-tested
    ASSERT((this->timer_ != NOT_ON_TIMER), "Invalid pin number");
    rdn::setupAnalogOutputPin(this->pin_);
  }

  int value() {
    return this->value_;
  }

  void write(int val) {
    rdn::analogWriteUnchecked(this->timer_, val);
    this->value_ = val;
  }

protected:
  uint8_t timer_;
  int value_ = 0;
};

#endif
