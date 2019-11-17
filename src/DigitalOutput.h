#ifndef __YPS_DIGITALOUTPUT_H__
#define __YPS_DIGITALOUTPUT_H__

class DigitalOutput {
public:
  DigitalOutput(uint8_t pin)
  : pinNr(pin)
  , m_value(0)
  {
    pinMode(this->pinNr, OUTPUT);
  }

  uint8_t pin() {
    return this->pinNr;
  }

  int value() {
    return m_value;
  }

  bool isHigh() {
    return m_value == HIGH;
  }

  bool isLow() {
    return m_value == LOW;
  }

  void write(int val) {
    __yps_internal::_digitalWrite(this->pinNr, val);
    this->m_value = val;
  }

  void toggle() {
    this->write(!this->value());
  }

protected:
  const uint8_t pinNr;
  int m_value;
};

#endif
