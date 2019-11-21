#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

bool observerState = false;
Observer observer;

Test test = Test("Observer")
    .sizeOf<Observer>(14)
    .benchmark("update()", 5.22*m, [](){ observer.update(); });

void setup() {
  observer.observe([](){ return observerState; });
  observerState = true; // change to trigger observer initially
  observer.onTrue([](){ observerState = false; });
  observer.onFalse([](){ observerState = true; });
}

void loop() {
  run(test);
}
