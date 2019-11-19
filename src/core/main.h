#ifndef __ESPRESSO_MAIN_H__
#define __ESPRESSO_MAIN_H__

AutoUpdated* AutoUpdated::root = 0;

void setup() {
  onSetup();
}

void loop() {
  AutoUpdated* it = AutoUpdated::root;
  if (it == 0) {
    return;
  }
  do {
    (*it).onLoop();
    it = (*it).next;
  } while (it != AutoUpdated::root);
}

#endif
