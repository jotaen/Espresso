#ifndef __RDN_H__
#define __RDN_H__

extern uint8_t analog_reference;

#ifdef __cplusplus
extern "C"{
#endif

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
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

  static inline void analogWriteUnchecked(uint8_t bit, volatile uint8_t* out, uint8_t timer, int val) {
    if (val == 0)
    {
      digitalWriteUnchecked(bit, out, LOW);
    }
    else if (val == 255)
    {
      digitalWriteUnchecked(bit, out, HIGH);
    }
    else
    {
      switch(timer)
      {
        // XXX fix needed for atmega8
        #if defined(TCCR0) && defined(COM00) && !defined(__AVR_ATmega8__)
        case TIMER0A:
          // connect pwm to pin on timer 0
          sbi(TCCR0, COM00);
          OCR0 = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR0A) && defined(COM0A1)
        case TIMER0A:
          // connect pwm to pin on timer 0, channel A
          sbi(TCCR0A, COM0A1);
          OCR0A = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR0A) && defined(COM0B1)
        case TIMER0B:
          // connect pwm to pin on timer 0, channel B
          sbi(TCCR0A, COM0B1);
          OCR0B = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR1A) && defined(COM1A1)
        case TIMER1A:
          // connect pwm to pin on timer 1, channel A
          sbi(TCCR1A, COM1A1);
          OCR1A = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR1A) && defined(COM1B1)
        case TIMER1B:
          // connect pwm to pin on timer 1, channel B
          sbi(TCCR1A, COM1B1);
          OCR1B = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR1A) && defined(COM1C1)
        case TIMER1C:
          // connect pwm to pin on timer 1, channel B
          sbi(TCCR1A, COM1C1);
          OCR1C = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR2) && defined(COM21)
        case TIMER2:
          // connect pwm to pin on timer 2
          sbi(TCCR2, COM21);
          OCR2 = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR2A) && defined(COM2A1)
        case TIMER2A:
          // connect pwm to pin on timer 2, channel A
          sbi(TCCR2A, COM2A1);
          OCR2A = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR2A) && defined(COM2B1)
        case TIMER2B:
          // connect pwm to pin on timer 2, channel B
          sbi(TCCR2A, COM2B1);
          OCR2B = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR3A) && defined(COM3A1)
        case TIMER3A:
          // connect pwm to pin on timer 3, channel A
          sbi(TCCR3A, COM3A1);
          OCR3A = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR3A) && defined(COM3B1)
        case TIMER3B:
          // connect pwm to pin on timer 3, channel B
          sbi(TCCR3A, COM3B1);
          OCR3B = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR3A) && defined(COM3C1)
        case TIMER3C:
          // connect pwm to pin on timer 3, channel C
          sbi(TCCR3A, COM3C1);
          OCR3C = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR4A)
        case TIMER4A:
          //connect pwm to pin on timer 4, channel A
          sbi(TCCR4A, COM4A1);
          #if defined(COM4A0)   // only used on 32U4
          cbi(TCCR4A, COM4A0);
          #endif
          OCR4A = val;  // set pwm duty
          break;
        #endif
        
        #if defined(TCCR4A) && defined(COM4B1)
        case TIMER4B:
          // connect pwm to pin on timer 4, channel B
          sbi(TCCR4A, COM4B1);
          OCR4B = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR4A) && defined(COM4C1)
        case TIMER4C:
          // connect pwm to pin on timer 4, channel C
          sbi(TCCR4A, COM4C1);
          OCR4C = val; // set pwm duty
          break;
        #endif
          
        #if defined(TCCR4C) && defined(COM4D1)
        case TIMER4D:       
          // connect pwm to pin on timer 4, channel D
          sbi(TCCR4C, COM4D1);
          #if defined(COM4D0)   // only used on 32U4
          cbi(TCCR4C, COM4D0);
          #endif
          OCR4D = val;  // set pwm duty
          break;
        #endif

                
        #if defined(TCCR5A) && defined(COM5A1)
        case TIMER5A:
          // connect pwm to pin on timer 5, channel A
          sbi(TCCR5A, COM5A1);
          OCR5A = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR5A) && defined(COM5B1)
        case TIMER5B:
          // connect pwm to pin on timer 5, channel B
          sbi(TCCR5A, COM5B1);
          OCR5B = val; // set pwm duty
          break;
        #endif

        #if defined(TCCR5A) && defined(COM5C1)
        case TIMER5C:
          // connect pwm to pin on timer 5, channel C
          sbi(TCCR5A, COM5C1);
          OCR5C = val; // set pwm duty
          break;
        #endif
      }
    }
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
