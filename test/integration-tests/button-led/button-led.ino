#include <Espresso.h>

const unsigned long duration = 1000;

DigitalInput button(7);
DigitalOutput led(13);
Timer ledTimer;
Observer buttonObserver;

void onSetup() {
  buttonObserver.observe([](){ return button.isHigh(); });
  buttonObserver.onTrue([](){
    led.write(HIGH);
    ledTimer.runOnce(duration);
  });
  ledTimer.onTrigger([](){ led.write(LOW); });
}
