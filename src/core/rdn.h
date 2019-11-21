#ifndef __RDN_H__
#define __RDN_H__

namespace rdn {

  bool isValidPin(uint8_t pin) {
    return digitalPinToPort(pin) != NOT_A_PIN;
  }

  static void pinModeUnchecked(uint8_t port, uint8_t bit, uint8_t mode) {
    volatile uint8_t *reg, *out;
    reg = portModeRegister(port);
    out = portOutputRegister(port);

    if (mode == INPUT) { 
      uint8_t oldSREG = SREG;
      cli();
      *reg &= ~bit;
      *out &= ~bit;
      SREG = oldSREG;
    } else if (mode == INPUT_PULLUP) {
      uint8_t oldSREG = SREG;
      cli();
      *reg &= ~bit;
      *out |= bit;
      SREG = oldSREG;
    } else {
      uint8_t oldSREG = SREG;
      cli();
      *reg |= bit;
      SREG = oldSREG;
    }
  }

  volatile uint8_t* setupDigitalInputPin(uint8_t pin, uint8_t bit, uint8_t mode) {
    uint8_t port = digitalPinToPort(pin);
    rdn::pinModeUnchecked(bit, port, mode);
    digitalRead(pin); // only way of ensuring PWM is turned off
    return portInputRegister(port);
  }

  volatile uint8_t* setupDigitalOutputPin(uint8_t pin, uint8_t bit, uint8_t mode) {
    uint8_t port = digitalPinToPort(pin);
    rdn::pinModeUnchecked(bit, port, mode);
    digitalWrite(pin, 0); // only way of ensuring PWM is turned off
    return portOutputRegister(port);
  }

  inline void digitalWriteUnchecked(uint8_t bit, volatile uint8_t* out, uint8_t val) {
    uint8_t oldSREG = SREG;
    cli();

    if (val == LOW) {
      *out &= ~bit;
    } else {
      *out |= bit;
    }

    SREG = oldSREG;
  }

  inline int digitalReadUnchecked(uint8_t bit, volatile uint8_t* in) {
    if (*in & bit) {
      return HIGH;
    }
    return LOW;
  }

}

#endif
