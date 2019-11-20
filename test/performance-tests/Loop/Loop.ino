#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

Loop looper;

Test test = Test("Loop")
    .sizeOf<Loop>(7)
    .benchmark("update()", 2.64*m, [](){ looper.update(); });

void setup() {
  looper.onTrigger([](){});
}

void loop() {
  run(test);
}
