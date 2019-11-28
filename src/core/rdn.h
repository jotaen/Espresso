#ifndef __RDN_H__
#define __RDN_H__

extern uint8_t analog_reference;

#ifdef __cplusplus
extern "C"{
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#ifdef __cplusplus
} // extern "C"
#endif

class rdn {
public:
  static bool isValidPin(uint8_t pin) {
    return digitalPinToPort(pin) != NOT_A_PIN;
  }

  static volatile uint8_t* setupDigitalInputPin(uint8_t pin, uint8_t bit, uint8_t mode) {
    uint8_t port = digitalPinToPort(pin);
    rdn::pinModeUnchecked(bit, port, mode);
    digitalRead(pin); // only way of ensuring PWM is turned off
    return portInputRegister(port);
  }

  static volatile uint8_t* setupDigitalOutputPin(uint8_t pin, uint8_t bit) {
    uint8_t port = digitalPinToPort(pin);
    rdn::pinModeUnchecked(bit, port, OUTPUT);
    digitalWrite(pin, 0); // only way of ensuring PWM is turned off
    return portOutputRegister(port);
  }

  static inline void digitalWriteUnchecked(uint8_t bit, volatile uint8_t* out, uint8_t val) {
    uint8_t oldSREG = SREG;
    cli();

    if (val == LOW) {
      *out &= ~bit;
    } else {
      *out |= bit;
    }

    SREG = oldSREG;
  }

  static inline int digitalReadUnchecked(uint8_t bit, volatile uint8_t* in) {
    if (*in & bit) {
      return HIGH;
    }
    return LOW;
  }

  static inline uint8_t analogPinToPoc(uint8_t pin) {
    #if defined(analogPinToChannel)
    #if defined(__AVR_ATmega32U4__)
      if (pin >= 18) pin -= 18; // allow for channel or pin numbers
    #endif
      pin = analogPinToChannel(pin);
    #elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
      if (pin >= 54) pin -= 54; // allow for channel or pin numbers
    #elif defined(__AVR_ATmega32U4__)
      if (pin >= 18) pin -= 18; // allow for channel or pin numbers
    #elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
      if (pin >= 24) pin -= 24; // allow for channel or pin numbers
    #else
      if (pin >= 14) pin -= 14; // allow for channel or pin numbers
    #endif
    return pin;
  }

  static inline void analogReadInit(uint8_t poc) {
    #if defined(ADCSRB) && defined(MUX5)
      ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((poc >> 3) & 0x01) << MUX5);
    #endif

    #if defined(ADMUX)
    #if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
      ADMUX = (analog_reference << 4) | (poc & 0x07);
    #else
      ADMUX = (analog_reference << 6) | (poc & 0x07);
    #endif
    #endif

    #if defined(ADCSRA) && defined(ADCL)
      sbi(ADCSRA, ADSC);
    #endif
  }

  static inline bool analogReadInProgress() {
    #if defined(ADCSRA) && defined(ADCL)
    return bit_is_set(ADCSRA, ADSC);
    #else
    return false;
    #endif
  }

  static inline int analogReadObtain() {
    uint8_t low, high;
    #if defined(ADCSRA) && defined(ADCL)
      low  = ADCL;
      high = ADCH;
    #else
      low  = 0;
      high = 0;
    #endif

    return (high << 8) | low;
  }

private:
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

};

#endif
