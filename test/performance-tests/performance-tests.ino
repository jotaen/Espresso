#include <Espresso.h>
#include "lib.h"

CHECK(
  test<DigitalInput>("DigitalInput", 4),
  test<DigitalOutput>("DigitalOutput", 6),
  test<Observer>("Observer", 14),
  test<Metronome>("Metronome", 15),
  test<Timer>("Timer", 15),
);

void onSetup() {
  Serial.begin(9600);
  for(auto & r : results) printout(r);
  while(true);
}
