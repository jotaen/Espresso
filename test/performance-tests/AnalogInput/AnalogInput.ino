#define ESPRESSO_NOBLACKLISTING
#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

AnalogInput analogInput(2);

Test test = Test("AnalogInput")
    .sizeOf<AnalogInput>(8)
    .benchmark("REFERENCE analogRead()", 112*m, [](){
      analogRead(1);
    })
    .benchmark("value()", 112.0*m, [](){ analogInput.valueBlocking(); });

void setup() {}

void loop() {
  run(test);
}
