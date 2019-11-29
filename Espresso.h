#ifndef __ESPRESSO_H__
#define __ESPRESSO_H__

#include <Arduino.h>

#include "config.h"

#include "src/logger.h"
#include "src/DigitalInput.h"
#include "src/DigitalOutput.h"
#include "src/AnalogInput.h"
#include "src/AnalogOutput.h"
#include "src/Observer.h"
#include "src/Timer.h"
#include "src/Loop.h"
#include "src/LoopBenchmark.h"
#include "src/SerialEvent.h"

void onSetup();

#ifndef ESPRESSO_NOBLACKLISTING
  #define pinMode _BLACKLISTED_pinMode_
  #define digitalWrite _BLACKLISTED_digitalWrite_
  #define digitalRead _BLACKLISTED_digitalRead_
#endif

#ifndef ESPRESSO_INCLUDES_ONLY
  #include "src/core/main.h"
#endif

#endif
