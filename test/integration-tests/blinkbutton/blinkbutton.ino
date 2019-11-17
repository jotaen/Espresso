#include <yps.h>

const unsigned long frequency = 100;

DigitalInput button = DigitalInput(4);
DigitalOutput led = DigitalOutput(6);
Metronome ledBlinker = Metronome([](){ led.toggle(); });

Actor onButtonHigh = Actor(
  []()->bool { return button.isHigh(); },
  [](){ if (!ledBlinker.isActive()) {ledBlinker.runMillis(frequency);} }
);

Actor onButtonLow = Actor(
  []()->bool { return button.isLow(); },
  [](){ ledBlinker.stop(); led.write(LOW); }
);

void onSetup() {}
