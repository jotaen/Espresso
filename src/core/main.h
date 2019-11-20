#ifndef __ESPRESSO_MAIN_H__
#define __ESPRESSO_MAIN_H__

#include "AutoUpdated.h"

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
    (*it).update();
    it = (*it).next;
  }
  #ifdef VIRTUINO
  while(it != AutoUpdated::root);
  #else
  while(true);
  #endif
}

#endif
