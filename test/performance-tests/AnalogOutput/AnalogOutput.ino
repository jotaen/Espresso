#define ESPRESSO_NOBLACKLISTING
#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

AnalogOutput analogOutput(6);

Test test = Test("AnalogOutput")
    .sizeOf<AnalogOutput>(7)
    .benchmark("REFERENCE digitalWrite() with PWM", 4.78*m, [](){
      analogWrite(5, HIGH); // pin with PWM
    })
    .benchmark("write()", 2.39*m, [](){ analogOutput.write(200); });

void setup() {}

void loop() {
  run(test);
}
