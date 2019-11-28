#include <Espresso.h>

DigitalOutput led(13);
AnalogInput poti(0);
Timer ledBlinker;
Loop looper;

short interval(int analogValue) {
  return 100 + (900 * analogValue / 255);
}

void onSetup() {
  ledBlinker.onTrigger([](){ led.toggle(); });
  ledBlinker.run(interval(poti.value()));
  looper.onTrigger([](){ ledBlinker.interval(interval(poti.value())); });
}
