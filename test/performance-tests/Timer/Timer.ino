#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

Timer timer;

Test test = Test("Timer")
    .sizeOf<Timer>(11)
    .benchmark("update()", 2.77*m, [](){ timer.update(); });

void setup() {
  timer.onTrigger([](){ timer.start(0); });
  timer.start(0);
}

void loop() {
  run(test);
}
