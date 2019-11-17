#include <yps.h>

const unsigned long frequency = 100;

DigitalInput button = DigitalInput(4);
DigitalOutput led = DigitalOutput(6);
Metronome ledBlinker = Metronome();
Observer buttonObserver = Observer([]()->bool { return button.isHigh(); });

void onSetup() {
  ledBlinker.onTrigger([](){ led.toggle(); });
  buttonObserver.onTrue([](){ ledBlinker.runMillis(frequency); });
  buttonObserver.onFalse([](){ ledBlinker.stop(); led.write(LOW); });
}
