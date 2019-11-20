#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include <test/performance-tests/lib.h>

Metronome metronome;

Test test = Test("Metronome")
    .sizeOf<Metronome>(15)
    .benchmark("update()", 6.35*m, [](){ metronome.update(); });

void setup() {
  metronome.onTrigger([](){});
  metronome.run(0);
}

void loop() {
  run(test);
}
