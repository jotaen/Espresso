#define CATCH_CONFIG_MAIN
#include <Virtuino.h>

namespace callspy {
  unsigned int _counter;

  void Void() {
    _counter++;
  }

  void reset() {
    _counter = 0;
  }

  bool hasBeenCalled() {
    return _counter > 0;
  }

  unsigned int counter() {
    return _counter;
  }
}

#include <Espresso.h>

void Virtuino::clear() {
  Device::clearRoot();
  Virtuino::start();
}

void onSetup() {}

#include "../src/core/Device.spec.h"
#include "../src/Observer.spec.h"
#include "../src/Timer.spec.h"
#include "../src/Metronome.spec.h"
#include "../src/DigitalInput.spec.h"
#include "../src/DigitalOutput.spec.h"
