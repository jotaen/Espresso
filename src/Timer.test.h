#include "../test.h"
#include "Timer.h"

TEST_CASE("[Timer]") {

  callspy::reset();
  World::reset();

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
    REQUIRE(callspy::reporter.count == 1);
  }

  SECTION("The handler function should be invoked recurringly") {
    unsigned long interval = 100;
    Timer t = Timer(callspy::Void);
    t.runMillis(interval);
    World::elapseMillis(3*interval);
    REQUIRE(callspy::reporter.hasBeenCalled);
    REQUIRE(callspy::reporter.count == 3);
  }

}
