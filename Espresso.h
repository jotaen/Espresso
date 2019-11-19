#ifndef __ESPRESSO_H__
#define __ESPRESSO_H__

#define pinMode _BLACKLISTED_pinMode_
#define digitalWrite _BLACKLISTED_digitalWrite_
#define digitalRead _BLACKLISTED_digitalRead_

#include <Arduino.h>

#include "src/Observer.h"
#include "src/Timer.h"
#include "src/Metronome.h"
#include "src/DigitalInput.h"
#include "src/DigitalOutput.h"

void onSetup();

#include "src/core/main.h"
#endif
