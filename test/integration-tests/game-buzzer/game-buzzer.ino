#include <Espresso.h>

const unsigned long duration = 1000;

DigitalInput buzzer1(6);
DigitalInput buzzer2(7);
DigitalInput resetButton(8);
DigitalOutput lightTeam1(11);
DigitalOutput lightTeam2(12);
DigitalOutput sound(13);
Timer soundTimer;
Observer buzzerObserver;
Observer resetObserver;

void reset() {
  lightTeam1.write(LOW);
  lightTeam2.write(LOW);
  buzzerObserver.enable();
}

void buzzer() {
  sound.write(HIGH);
  if (buzzer1.isHigh()) {
    lightTeam1.write(HIGH);
  } else {
    lightTeam2.write(HIGH);
  }
  soundTimer.onTrigger([](){ sound.write(LOW); });
  soundTimer.runOnce(500);
  buzzerObserver.disable();
}

void onSetup() {
  buzzerObserver.observe([](){ return buzzer1.isHigh() || buzzer2.isHigh(); });
  buzzerObserver.onTrue(buzzer);
  resetObserver.observe([](){ return resetButton.isHigh(); });
  resetObserver.onTrue(reset);
}
