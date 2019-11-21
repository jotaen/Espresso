#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

Timer timer;

Test test = Test("Timer")
    .sizeOf<Timer>(16)
    .benchmark("update()", 5.34*m, [](){ timer.update(); });

void setup() {
  timer.onTrigger([](){});
  timer.run(0);
}

void loop() {
  run(test);
}
