#define CATCH_CONFIG_MAIN

namespace callspy {
  struct {
    bool hasBeenCalled;
    int count;
  } reporter;

  void Void() {
    reporter.hasBeenCalled = true;
    reporter.count++;
  }

  void reset() {
    reporter.hasBeenCalled = false;
    reporter.count = 0;
  }
}

void onSetup() {}

#include "../src/Device.spec.h"
#include "../src/Actor.spec.h"
#include "../src/Timer.spec.h"
#include "../src/Metronome.spec.h"
#include "../src/DigitalInput.spec.h"
#include "../src/DigitalOutput.spec.h"
