#include <Espresso.h>
#include "lib.h"

Result results[] = {

  Test<DigitalInput>("DigitalInput")
    .expectSize(4),
  Test<DigitalOutput>("DigitalOutput")
    .expectSize(6),
  Test<Observer>("Observer")
    .expectSize(14),
  Test<Metronome>("Metronome")
    .expectSize(15),
  Test<Timer>("Timer")
    .expectSize(15),
  Test<Loop>("Loop")
    .expectSize(7),
};

void onSetup() {
  Serial.begin(9600);
  for(auto & r : results) printout(r);
  while(true);
}
