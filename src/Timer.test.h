#include "../lib/catch.hpp"
#include "yps.h"
#include "../test.h"
#include "Timer.h"
#include "utils.h"

TEST_CASE("[Timer]") {

  callspy::reset();

  SECTION("A Timer is a Device") {
    Timer t = Timer(noop);
    Device& d = t; // The “assertion” is that this compiles
  }

  SECTION("The handler function should not be invoked after the time has elapsed") {
    Timer t = Timer(callspy::Void);
    World::loopOnce();
    REQUIRE(!callspy::reporter.hasBeenCalled);
  }

  SECTION("The handler function should be invoked after time has passed") {
    unsigned long interval = 100;
    Timer t = Timer(callspy::Void);
    t.runMillis(interval);
    World::elapseMillis(interval);
    REQUIRE(callspy::reporter.hasBeenCalled);
  }

}
