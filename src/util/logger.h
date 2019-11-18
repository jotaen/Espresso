#ifndef __ESPRESSO_DEBUG_H__
#define __ESPRESSO_DEBUG_H__

#include <Arduino.h>
#include <memory>

class Device;

namespace logger {

  void init(long serialSpeed = 9600) {
    Serial.begin(serialSpeed);
  }

  template<class T>
  void info(const char* message, T* origin) {
    std::cout << std::addressof(origin) << std::endl;
    Serial.println(message);
  }

}

#endif
