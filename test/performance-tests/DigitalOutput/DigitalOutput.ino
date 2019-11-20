#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

DigitalOutput digitalOutput(4);

Test test = Test("DigitalOutput")
    .sizeOf<DigitalOutput>(6)
    .benchmark("write()", 2.46*m, [](){ digitalOutput.write(HIGH); })
    .benchmark("toggle()", 3.11*m, [](){ digitalOutput.toggle(); });

void setup() {}

void loop() {
  run(test);
}
