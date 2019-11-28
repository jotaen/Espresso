#include <Espresso.h>

DigitalOutput red(1);
DigitalOutput yellow(2);
DigitalOutput green(3);
Timer switcher;
DigitalInput button(4);
Observer buttonObserver;

void toRed();
void toGreen();

void onSetup() {
  green.write(HIGH);
  buttonObserver.observe([](){ return button.isHigh(); });
  buttonObserver.onTrue(toRed);
}

void toRed() {
  buttonObserver.disable();
  green.write(LOW);
  yellow.write(HIGH);
  switcher.onTrigger([](){
    yellow.write(LOW);
    red.write(HIGH);
    buttonObserver.onTrue(toGreen);
    buttonObserver.enable();
  });
  switcher.runOnce(1000);
}

void toGreen() {
  buttonObserver.disable();
  yellow.write(HIGH);
  switcher.onTrigger([](){
    red.write(LOW);
    yellow.write(LOW);
    green.write(HIGH);
    buttonObserver.onTrue(toRed);
    buttonObserver.enable();
  });
  switcher.runOnce(1000);
}
