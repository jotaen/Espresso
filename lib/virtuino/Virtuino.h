#ifndef __VIRTUINO_H__
#define __VIRTUINO_H__

#include <iostream>
#include <map>
#include <string>
#include <Arduino.h>

#define VIRTUINO

namespace rdn {
  volatile uint8_t* setupDigitalInputPin(uint8_t, uint8_t, uint8_t);
  volatile uint8_t* setupDigitalOutputPin(uint8_t, uint8_t, uint8_t);
  void digitalWriteUnchecked(uint8_t, volatile uint8_t*, uint8_t);
  int digitalReadUnchecked(uint8_t, volatile uint8_t*);
}

typedef std::string String;
#define String(x) std::to_string(x)

class Virtuino {
public:
  Virtuino() {
    millis_ = 0;
    digitalOutputs_.clear();
    digitalInputs_.clear();
    setup();
  }

  void flush() {
    loop();
  }

  void elapseMillis(unsigned long m) {
    const unsigned int target = millis_ + m;
    while(millis_ < target) {
      millis_ += 1;
      flush();
    }
  }

  void freezeMillis(unsigned long m) {
    millis_ += m;
    flush();
  }

  uint8_t checkPinMode(uint8_t pin) {
    return pinModes_.at(pin); // throws if key not set
  }

  void setDigitalInput(uint8_t pin, int val) {
    if (checkPinMode(pin) != INPUT) {
      throw std::invalid_argument("`pin`");
    }
    digitalInputs_[pin] = val;
    flush();
  }

  int checkDigitalOutput(uint8_t pin) {
    if (checkPinMode(pin) != OUTPUT) {
      throw std::invalid_argument("`pin`");
    }
    return digitalOutputs_[pin];
  }

private:
  friend unsigned long millis(void);
  friend int digitalRead(uint8_t);
  friend void digitalWrite(uint8_t, uint8_t);
  friend volatile uint8_t* rdn::setupDigitalInputPin(uint8_t, uint8_t, uint8_t);
  friend volatile uint8_t* rdn::setupDigitalOutputPin(uint8_t, uint8_t, uint8_t);
  friend void rdn::digitalWriteUnchecked(uint8_t, volatile uint8_t*, uint8_t);
  friend int rdn::digitalReadUnchecked(uint8_t, volatile uint8_t*);

  static unsigned long millis_;
  static std::map<uint8_t, uint8_t> pinModes_;
  static std::map<uint8_t, int> digitalInputs_;
  static std::map<uint8_t, int> digitalOutputs_;
};

unsigned long Virtuino::millis_ = 0;
std::map<uint8_t, uint8_t> Virtuino::pinModes_;
std::map<uint8_t, int> Virtuino::digitalInputs_;
std::map<uint8_t, int> Virtuino::digitalOutputs_;

#include "rdn.h"

unsigned long millis(void) {
  return Virtuino::millis_;
}

int digitalRead(uint8_t pin) {
    return Virtuino::digitalInputs_[pin];
}

void digitalWrite(uint8_t pin, uint8_t val) {
  Virtuino::digitalOutputs_[pin] = val;
}

uint8_t digitalPinToBitMask(uint8_t pin) {
  return pin;
}

struct SoftwareSerial {
  static const int DEC = 10;

  void begin(long speed);

  size_t print(const String &);
  size_t print(const char[]);
  // size_t print(char);
  // size_t print(unsigned char, int = DEC);
  // size_t print(int, int = DEC);
  // size_t print(unsigned int, int = DEC);
  // size_t print(long, int = DEC);
  size_t print(unsigned long, int = DEC);
  // size_t print(double, int = 2);

  size_t println(const String &s);
  size_t println(const char[]);
  // size_t println(char);
  // size_t println(unsigned char, int = DEC);
  // size_t println(int, int = DEC);
  // size_t println(unsigned int, int = DEC);
  // size_t println(long, int = DEC);
  // size_t println(unsigned long, int = DEC);
  // size_t println(double, int = 2);
  // size_t println(void);
} Serial;

void SoftwareSerial::begin(long speed) {}

size_t SoftwareSerial::print(const String& s) {
  std::cout << s;
  return 0;
}

size_t SoftwareSerial::print(const char* s) {
  std::cout << s;
  return 0;
}

size_t SoftwareSerial::print(unsigned long x, int base) {
  std::cout << x;
  return 0;
}

size_t SoftwareSerial::println(const String& s) {
  std::cout << s << std::endl;
  return 0;
}

size_t SoftwareSerial::println(const char* s) {
  std::cout << s << std::endl;
  return 0;
}

#endif
