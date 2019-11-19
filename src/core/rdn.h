#ifndef __RDN_H__
#define __RDN_H__

namespace rdn {

  bool isValidPin(uint8_t pin) {
    return digitalPinToPort(pin) != NOT_A_PIN;
  }

  void pinModeUnchecked(uint8_t bit, uint8_t port, uint8_t mode) {
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

  void digitalWriteUnchecked(uint8_t bit, uint8_t port, uint8_t val) {
    volatile uint8_t *out;
    out = portOutputRegister(port);

    uint8_t oldSREG = SREG;
    cli();

    if (val == LOW) {
      *out &= ~bit;
    } else {
      *out |= bit;
    }

    SREG = oldSREG;
  }

  int digitalReadUnchecked(uint8_t bit, volatile uint8_t* portInputRegister) {
    if (*portInputRegister & bit) {
      return HIGH;
    }
    return LOW;
  }

}

#endif
