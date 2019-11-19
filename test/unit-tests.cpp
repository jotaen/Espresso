#define CATCH_CONFIG_MAIN
#include <Virtuino.h>
#include <Espresso.h>

#include "../src/core/AutoUpdated.spec.cpp"
#include "../src/core/DigitalPin.spec.cpp"
#include "../src/Observer.spec.cpp"
#include "../src/Timer.spec.cpp"
#include "../src/Metronome.spec.cpp"
#include "../src/DigitalInput.spec.cpp"
#include "../src/DigitalOutput.spec.cpp"

void Virtuino::clear() {
  AutoUpdated::root = 0;
  Virtuino::start();
}

void onSetup() {}
