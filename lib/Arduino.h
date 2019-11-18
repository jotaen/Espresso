#ifndef __ESPRESSO_ARDUINO_H__
#define __ESPRESSO_ARDUINO_H__

///////////////////////////////////////////////////////////////////////////////
// Declarations from original Arduino headers
// https://github.com/arduino/ArduinoCore-avr/tree/master/cores/arduino
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>

typedef uint8_t byte;
#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);

unsigned long millis(void);

void setup();
void loop();

///////////////////////////////////////////////////////////////////////////////
// Look-alike substitutions
///////////////////////////////////////////////////////////////////////////////

#include <string>
typedef std::string String;

struct SoftwareSerial {
  void begin(long speed);
  size_t print(const String &);
  size_t println(const String &s);
} Serial;

#endif
