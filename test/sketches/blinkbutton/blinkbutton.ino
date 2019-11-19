#include <Espresso.h>

const unsigned long frequency = 100;

DigitalInput button(7);
DigitalOutput led(13);
Metronome ledBlinker;
Observer buttonObserver([]()->bool { return button.isHigh(); });

void onSetup() {
  ledBlinker.onTrigger([](){ led.toggle(); });
  buttonObserver.onTrue([](){ ledBlinker.runMillis(frequency); });
  buttonObserver.onFalse([](){ ledBlinker.stop(); led.write(LOW); });
}
