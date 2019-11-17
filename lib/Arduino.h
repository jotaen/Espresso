#ifndef __YPS_ARDUINO_H__
#define __YPS_ARDUINO_H__

////////////////////////////////////////////
// Declarations from original <Arduino.h> //
////////////////////////////////////////////

#include <stdlib.h>
#include <map>

typedef uint8_t byte;
#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);

unsigned long millis(void);


////////////////////////////////////////////
// Fixtures for yps testing environment ////
////////////////////////////////////////////

#include "../src/Device.h"
Device* Device::rootDevice = 0;

namespace Arduino {
  unsigned long __millis;
  std::map<uint8_t, int> __pinModes;
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

  void setDigitalInput(uint8_t pin, int val) {
    if (Arduino::__pinModes[pin] != INPUT) {
      throw;
    }
    Arduino::__digitalInputs[pin] = val;
    flush();
  }

  int checkDigitalOutput(uint8_t pin) {
    if (Arduino::__pinModes[pin] != OUTPUT) {
      throw;
    }
    return Arduino::__digitalOutputs[pin];
  }
}

void pinMode(uint8_t pin, uint8_t mode) {
  Arduino::__pinModes[pin] = mode;
}

void digitalWrite(uint8_t pin, uint8_t val) {
  if (Arduino::__pinModes[pin] != OUTPUT) {
    throw;
  }
  Arduino::__digitalOutputs[pin] = val;
}

int digitalRead(uint8_t pin) {
  if (Arduino::__pinModes[pin] != INPUT) {
    throw;
  }
  return Arduino::__digitalInputs[pin];
}

unsigned long millis(void) {
  return Arduino::__millis;
}

#endif
