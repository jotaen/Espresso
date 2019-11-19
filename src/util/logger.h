#ifndef __ESPRESSO_DEBUG_H__
#define __ESPRESSO_DEBUG_H__

#include <Arduino.h>

namespace logger {

  template<class T>
  inline void info(const char* message, T* origin);
  inline void info(const char* message);

  template<class T>
  inline void warning(const char* message, T* origin);
  inline void warning(const char* message);

  template<class T>
  inline void error(const char* message, T* origin);
  inline void error(const char* message);

  inline void init(long serialSpeed = 9600);

  template<class T>
  void log(const char* level, const char* message, T* origin = 0);
}

  #ifdef ESPRESSO_LOGGING

  template<class T>
  inline void logger::info(const char* message, T* origin) {
    log("INFO", message, origin);
  }
  inline void logger::info(const char* message) {
    info(message, (void*)0);
  }

  template<class T>
  inline void logger::warning(const char* message, T* origin) {
    log("WARNING", message, origin);
  }
  inline void logger::warning(const char* message) {
    warning(message, (void*)0);
  }

  template<class T>
  inline void logger::error(const char* message, T* origin) {
    log("ERROR", message, origin);
  }
  inline void logger::error(const char* message) {
    error(message, (void*)0);
  }

  inline void logger::init(long serialSpeed) {
    Serial.begin(serialSpeed);
  }

  template<class T>
  void logger::log(const char* level, const char* message, T* origin) {
    // format: "hh:mm:ss.xxx"
    const unsigned long now = millis();
    char timestamp [13];
    sprintf (timestamp, "%02lu:%02lu:%02lu.%03lu"
      , (now / 60 / 60 / 1000) % 24 // hour
      , (now / 60 / 1000) % 60 // minute
      , (now / 1000) % 60 // seconds
      , (now % 1000)
    );

    Serial.print(timestamp);
    Serial.print(" ");
    Serial.print(level);
    if (origin != 0) {
      Serial.print(" [");
      Serial.print((uintptr_t) origin, 16);
      Serial.print("]");
    }
    Serial.print(": ");
    Serial.print(message);
    Serial.println("");
  }

  #else

  template<class T>
  inline void logger::info(const char* message, T* origin) {}
  inline void logger::info(const char* message) {}

  template<class T>
  inline void logger::warning(const char* message, T* origin) {}
  inline void logger::warning(const char* message) {}

  template<class T>
  inline void logger::error(const char* message, T* origin) {}
  inline void logger::error(const char* message) {}

  inline void logger::init(long serialSpeed) {}

  template<class T>
  void logger::log(const char* level, const char* message, T* origin) {}

  #endif

#endif
