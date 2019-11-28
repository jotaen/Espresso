#define ESPRESSO_NOBLACKLISTING
#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

DigitalInput digitalInput(2);

Test test = Test("DigitalInput")
    .sizeOf<DigitalInput>(4)
    .benchmark("REFERENCE digitalRead()", 3.96*m, [](){
      digitalRead(1);
    })
    .benchmark("value()", 1.45*m, [](){ digitalInput.value(); });

void setup() {}

void loop() {
  run(test);
}
