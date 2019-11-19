#ifndef __ESPRESSO_H__
#define __ESPRESSO_H__

#define _BLACKLISTED_pinMode_ pinMode
#define _BLACKLISTED_digitalWrite_ digitalWrite
#define _BLACKLISTED_digitalRead_ digitalRead

#include <Arduino.h>

#include "config.h"
#include "src/util/logger.h"
#include "src/util/macros.h"

#include "src/DigitalInput.h"
#include "src/DigitalOutput.h"
#include "src/Observer.h"
#include "src/Timer.h"
#include "src/Metronome.h"
#include "src/Loop.h"

#include "src/util/LoopBenchmark.h"

void onSetup();

#include "src/core/main.h"
#endif
