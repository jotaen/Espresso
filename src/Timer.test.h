#include "../test.h"
#include "Timer.h"

TEST_CASE("[Timer]") {

  callspy::reset();
  World::reset();

  SECTION("A Timer is a Device") {
    Timer t = Timer(noop);
    Device& d = t; // The “assertion” is that this compiles
  }

  SECTION("The handler function should not be invoked before the time has elapsed") {
    Timer t = Timer(callspy::Void);
    World::loopOnce();
    REQUIRE(!callspy::reporter.hasBeenCalled);
  }

  SECTION("`runMillis`: The handler function should be invoked after time has elapsed") {
    unsigned long interval = 10;
    Timer t = Timer(callspy::Void);
    t.runMillis(interval);
    World::elapseMillis(interval);
    REQUIRE(callspy::reporter.hasBeenCalled);
    REQUIRE(callspy::reporter.count == 1);
  }

  SECTION("`runMillis`: The handler function should be invoked recurringly") {
    unsigned long interval = 10;
    Timer t = Timer(callspy::Void);
    t.runMillis(interval);
    World::elapseMillis(3*interval);
    REQUIRE(callspy::reporter.hasBeenCalled);
    REQUIRE(callspy::reporter.count == 3);
  }

  SECTION("`runMillis`: The handler should not be invoked anymore after the timer was stopped") {
    unsigned long interval = 10;
    Timer t = Timer(callspy::Void);
    t.runMillis(interval);
    World::elapseMillis(3*interval);
    t.stop();
    World::elapseMillis(3*interval);
    REQUIRE(callspy::reporter.count == 3);
  }

  SECTION("`onceMillis`: The handler should not be invoked once after the elapsed time") {
    unsigned long interval = 10;
    Timer t = Timer(callspy::Void);
    t.onceMillis(interval);
    World::elapseMillis(3*interval);
    REQUIRE(callspy::reporter.hasBeenCalled);
    REQUIRE(callspy::reporter.count == 1);
  }

}
