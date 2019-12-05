#include <Espresso.h>

DigitalOutput red(1);
DigitalOutput yellow(2);
DigitalOutput green(3);
Timer switcher;
DigitalInput button(4);
Observer<bool> buttonObserver;

void toRed();
void toGreen();

void onSetup() {
  green.write(HIGH);
  buttonObserver.observe([](){ return button.isHigh(); });
  buttonObserver.onChange([](bool high) { if (high) toRed(); });
}

void toRed() {
  buttonObserver.disable();
  green.write(LOW);
  yellow.write(HIGH);
  switcher.onTrigger([](){
    red.write(HIGH);
    yellow.write(LOW);
    buttonObserver.onChange([](bool high) { if (high) toGreen(); });
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
    buttonObserver.onChange([](bool high) { if (high) toRed(); });
    buttonObserver.enable();
  });
  switcher.runOnce(1000);
}
