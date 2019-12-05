#include <Espresso.h>

DigitalInput button(7);
Observer<bool> buttonObserver;
Timer debouncer;
unsigned int triggerCount = 0;
unsigned int debounceTime = 30;

void onSetup() {
  debouncer.onTrigger([](){ triggerCount++; });
  buttonObserver.observe([](){ return button.isHigh(); });
  buttonObserver.onChange([](bool high){ high ? debouncer.runOnce(debounceTime) : debouncer.stop(); });
}
