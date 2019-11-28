#include <Espresso.h>

DigitalInput button(7);
Observer buttonObserver;
Timer debouncer;
unsigned int triggerCount = 0;
unsigned int debounceTime = 30;

void onSetup() {
  debouncer.onTrigger([](){ triggerCount++; });
  buttonObserver.observe([](){ return button.isHigh(); });
  buttonObserver.onTrue([](){ debouncer.runOnce(debounceTime); });
  buttonObserver.onFalse([](){ debouncer.stop(); });
}
