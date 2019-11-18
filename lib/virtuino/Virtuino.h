#ifndef __VIRTUINO_H__
#define __VIRTUINO_H__

#include <iostream>
#include <map>
#include <string>

#include <Arduino.h>

#define VIRTUINO_ENVIRONMENT true

typedef std::string String;

namespace Virtuino {
  unsigned long __millis;
  std::map<uint8_t, uint8_t> __pinModes;
  std::map<uint8_t, int> __digitalInputs;
  std::map<uint8_t, int> __digitalOutputs;

  void start() {
    __millis = 0;
    __digitalOutputs.clear();
    __digitalInputs.clear();
    ::setup();
  }

  void clear();

  void flush() {
    ::loop();
  }

  void elapseMillis(unsigned long m) {
    const unsigned int target = __millis + m;
    while(__millis < target) {
      __millis += 1;
      flush();
    }
  }

  void freezeMillis(unsigned long m) {
    __millis += m;
    flush();
  }

  uint8_t checkPinMode(uint8_t pin) {
    return __pinModes.at(pin); // throws if key not set
  }

  void setDigitalInput(uint8_t pin, int val) {
    if (checkPinMode(pin) != INPUT) {
      throw std::invalid_argument("`pin`");
    }
    __digitalInputs[pin] = val;
    flush();
  }

  int checkDigitalOutput(uint8_t pin) {
    if (checkPinMode(pin) != OUTPUT) {
      throw std::invalid_argument("`pin`");
    }
    return __digitalOutputs[pin];
  }
}

#include "rdn.h"

unsigned long millis(void) {
  return Virtuino::__millis;
}

uint8_t digitalPinToBitMask(uint8_t pin) {
  return pin;
}

uint8_t digitalPinToPort(uint8_t pin) {
  return pin;
}

struct SoftwareSerial {
  void begin(long speed);
  size_t print(const String &);
  size_t println(const String &s);
} Serial;

void SoftwareSerial::begin(long speed) {

}

size_t SoftwareSerial::print(const String &s) {
  return 0;
}

size_t SoftwareSerial::println(const String &s) {
  std::cout << s << std::endl;
  return 0;
}

#endif
