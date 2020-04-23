#include <Espresso.h>

const unsigned long duration = 1000;

DigitalInput button(7);
DigitalOutput led(13);
Timer ledTimer;
Observer<bool> buttonObserver;

void onSetup() {
  buttonObserver.observe([](){ return button.isHigh(); });
  buttonObserver.onChange([](bool isHigh){
    if (isHigh) {
      led.write(HIGH);
      ledTimer.runOnce(duration);
    }
  });
  ledTimer.onTrigger([](){ led.write(LOW); });
}
