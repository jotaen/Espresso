#ifndef __ESPRESSO_MAIN_H__
#define __ESPRESSO_MAIN_H__

#include "AutoUpdated.h"
#include "../util/logger.h"

AutoUpdated* AutoUpdated::root = 0;
bool DigitalPin::pinRegistry[64] = {false};

void setup() {
  logger::init();
  logger::info("System started");
  onSetup();
  logger::info("Setup complete");
}

void loop() {
  AutoUpdated* it = AutoUpdated::root;
  if (it == 0) {
    return;
  }
  do {
    (*it).onLoop();
    it = (*it).next;
  }
  #ifdef VIRTUINO
  while(it != AutoUpdated::root);
  #else
  while(true);
  #endif
}

#endif
