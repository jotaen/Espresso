#ifndef __ESPRESSO_DEBUG_H__
#define __ESPRESSO_DEBUG_H__

#include <Arduino.h>

namespace logger {

  void init(long serialSpeed = 9600) {
    Serial.begin(serialSpeed);
  }

  template<class T>
  String addressToString(T* ptr) {
    std::ostringstream address;
    address << (void const *)ptr;
    return address.str();
  }

  template<class T>
  void log(const char* level, T* origin, const char* message) {
    Serial.print(level);
    Serial.print(" [");
    Serial.print(addressToString(origin));
    Serial.print("]: ");
    Serial.print(message);
    Serial.println("");
  }

  template<class T>
  void info(T* origin, const char* message) {
    log("INFO", origin, message);
  }

  template<class T>
  void warning(T* origin, const char* message) {
    log("WARNING", origin, message);
  }

  template<class T>
  void error(T* origin, const char* message) {
    log("ERROR", origin, message);
  }
}

#endif
