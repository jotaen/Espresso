#ifndef __YPS_ARDUINO_H__
#define __YPS_ARDUINO_H__

/////////////////////////////////////////////////////////////////////////////////
// Declarations from original <Arduino.h>
// https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h
/////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>

typedef uint8_t byte;
#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);

unsigned long millis(void);


/////////////////////////////////////////////////////////////////////////////////
// Fixtures for yps testing environment
/////////////////////////////////////////////////////////////////////////////////

#include <map>
#include "../src/Device.h"
Device* Device::rootDevice = 0;

namespace Arduino {
  unsigned long __millis;
  std::map<uint8_t, uint8_t> __pinModes;
  std::map<uint8_t, int> __digitalInputs;
  std::map<uint8_t, int> __digitalOutputs;

  void start() {
    __millis = 0;
    __digitalOutputs.clear();
    onSetup();
  }

  void clear() {
    Device::clearRoot();
    __digitalInputs.clear();
    start();
  }

  void flush() {
    Device::loopOnce();
  }

  void elapseMillis(unsigned long m) {
    const unsigned int target = __millis + m;
    while(__millis < target) {
      __millis += 1;
      flush();
    }
  }

  uint8_t checkPinMode(uint8_t pin) {
    return __pinModes.at(pin); // throws if key not set
  }

  void setDigitalInput(uint8_t pin, int val) {
    if (checkPinMode(pin) != INPUT) {
      throw;
    }
    __digitalInputs[pin] = val;
    flush();
  }

  int checkDigitalOutput(uint8_t pin) {
    if (checkPinMode(pin) != OUTPUT) {
      throw;
    }
    return __digitalOutputs[pin];
  }
}

void pinMode(uint8_t pin, uint8_t mode) {
  Arduino::__pinModes[pin] = mode;
}

void digitalWrite(uint8_t pin, uint8_t val) {
  if (Arduino::checkPinMode(pin) != OUTPUT) {
    throw;
  }
  Arduino::__digitalOutputs[pin] = val;
}

int digitalRead(uint8_t pin) {
  if (Arduino::checkPinMode(pin) != INPUT) {
    throw;
  }
  return Arduino::__digitalInputs[pin];
}

unsigned long millis(void) {
  return Arduino::__millis;
}

#endif
