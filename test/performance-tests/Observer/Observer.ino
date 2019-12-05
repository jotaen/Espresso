#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

bool observerState = false;
Observer<bool> observer;

Test test = Test("Observer")
    .sizeOf<Observer<bool>>(13)
    .benchmark("update()", 5.16*m, [](){ observer.update(); });

void setup() {
  observer.observe([](){ return observerState; });
  observerState = true; // change to trigger observer initially
  observer.onChange([](bool s){ observerState = !s; });
}

void loop() {
  run(test);
}
