#include <Espresso.h>

const unsigned long frequency = 100;

DigitalInput button(7);
DigitalOutput led(13);
Timer ledBlinker;
Observer buttonObserver([]()->bool { return button.isHigh(); });

void onSetup() {
  ledBlinker.onTrigger([](){ led.toggle(); });
  buttonObserver.onTrue([](){ ledBlinker.run(frequency); });
  buttonObserver.onFalse([](){ ledBlinker.stop(); led.write(LOW); });
}
