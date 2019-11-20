#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

DigitalInput digitalInput(2);

Test test = Test("DigitalInput")
    .sizeOf<DigitalInput>(4)
    .benchmark("value()", 1.45*m, [](){ digitalInput.value(); });

void setup() {}

void loop() {
  run(test);
}
