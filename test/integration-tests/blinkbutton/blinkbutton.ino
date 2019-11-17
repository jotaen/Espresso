#include "yps.h"

DigitalInput button = DigitalInput(4);

bool led = false;

unsigned long frequency = 100;

Timer ledBlinker = Timer([](){ led = !led; });

Actor onButtonHigh = Actor(
  []()->bool { return button.isHigh(); },
  [](){ if (!ledBlinker.isActive()) {ledBlinker.runMillis(frequency);} }
);

Actor onButtonLow = Actor(
  []()->bool { return button.isLow(); },
  [](){ ledBlinker.stop(); led = false; }
);
