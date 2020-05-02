#ifndef __ESPRESSO_DIGITALOUTPUT_H__
#define __ESPRESSO_DIGITALOUTPUT_H__

/**
 * Represents a Digital Output Pin
 */
class DigitalOutput: public DigitalPin {
public:
  DigitalOutput(uint8_t pin)
  : DigitalPin(pin)
  , bit_(digitalPinToBitMask(pin))
  {
    this->outReg_ = rdn::setupDigitalOutputPin(this->pin_, this->bit_);
  }

  /**
   * Returns last value that was being written
   */
  int value() {
    return value_;
  }

  bool isHigh() {
    return value_ == HIGH;
  }

  bool isLow() {
    return value_ == LOW;
  }

  /**
   * Writes value to Pin
   */
  void write(int val) {
    rdn::digitalWriteUnchecked(this->bit_, this->outReg_, val);
    this->value_ = val;
  }

  /**
   * Toggles value (from HIGH to LOW or vice versa)
   */
  void toggle() {
    this->write(!this->value());
  }

protected:
  volatile uint8_t* outReg_;
  const uint8_t bit_;
  bool value_ = 0;
};

#endif
