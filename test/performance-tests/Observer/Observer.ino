#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

bool observerState = false;
Observer observer([](){ return observerState; });

Test test = Test("Observer")
    .sizeOf<Observer>(14)
    .benchmark("update()", 5.38*m, [](){ observer.update(); });

void setup() {
  observerState = true; // change to trigger observer initially
  observer.onTrue([](){ observerState = !observerState; });
  observer.onFalse([](){ observerState = !observerState; });
}

void loop() {
  run(test);
}
