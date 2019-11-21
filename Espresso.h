#ifndef __ESPRESSO_H__
#define __ESPRESSO_H__

#include <Arduino.h>

#include "config.h"
#include "src/util/logger.h"
#include "src/util/macros.h"
#include "src/util/LoopBenchmark.h"

#include "src/DigitalInput.h"
#include "src/DigitalOutput.h"
#include "src/Observer.h"
#include "src/Timer.h"
#include "src/Metronome.h"
#include "src/Loop.h"

void onSetup();

#define pinMode _BLACKLISTED_pinMode_
#define digitalWrite _BLACKLISTED_digitalWrite_
#define digitalRead _BLACKLISTED_digitalRead_

#ifndef ESPRESSO_INCLUDES_ONLY
  #include "src/core/main.h"
#endif
#endif
