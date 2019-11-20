#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

DigitalOutput digitalOutput(4);

Test test = Test("DigitalOutput")
    .sizeOf<DigitalOutput>(5)
    .benchmark("write()", 2.26*m, [](){ digitalOutput.write(HIGH); })
    .benchmark("toggle()", 2.58*m, [](){ digitalOutput.toggle(); });

void setup() {}

void loop() {
  run(test);
}
