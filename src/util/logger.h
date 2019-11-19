#ifndef __ESPRESSO_DEBUG_H__
#define __ESPRESSO_DEBUG_H__

#include <Arduino.h>

namespace logger {

  template<class T>
  inline void info(T* origin, const char* message);

  template<class T>
  inline void warning(T* origin, const char* message);

  template<class T>
  inline void error(T* origin, const char* message);

  inline void init(long serialSpeed = 9600);

  template<class T>
  String addressToString(T* ptr);

  template<class T>
  void log(const char* level, T* origin, const char* message);
}

  #ifdef ESPRESSO_LOGGING

  template<class T>
  inline void logger::info(T* origin, const char* message) {
    log("INFO", origin, message);
  }

  template<class T>
  inline void logger::warning(T* origin, const char* message) {
    log("WARNING", origin, message);
  }

  template<class T>
  inline void logger::error(T* origin, const char* message) {
    log("ERROR", origin, message);
  }

  inline void logger::init(long serialSpeed) {
    Serial.begin(serialSpeed);
  }

  template<class T>
  String logger::addressToString(T* ptr) {
    std::ostringstream address;
    address << (void const *)ptr;
    return address.str();
  }

  template<class T>
  void logger::log(const char* level, T* origin, const char* message) {
    Serial.print(level);
    Serial.print(" [");
    Serial.print(addressToString(origin));
    Serial.print("]: ");
    Serial.print(message);
    Serial.println("");
  }

  #else

  template<class T>
  inline void logger::info(T* origin, const char* message) {}

  template<class T>
  inline void logger::warning(T* origin, const char* message) {}

  template<class T>
  inline void logger::error(T* origin, const char* message) {}

  inline void logger::init(long serialSpeed) {}

  template<class T>
  String logger::addressToString(T* ptr) {}

  template<class T>
  void logger::log(const char* level, T* origin, const char* message) {}

  #endif

#endif
