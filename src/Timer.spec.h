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

  SECTION("`isActive`: Should inform about whether the timer is active or idling") {
    Timer t = Timer(noop);
    REQUIRE(t.isActive() == false);
    t.runMillis(10);
    REQUIRE(t.isActive());
    t.stop();
    REQUIRE(t.isActive() == false);
    t.onceMillis(10);
    REQUIRE(t.isActive());
    World::elapseMillis(50);
    REQUIRE(t.isActive() == false);
  }

  SECTION("`runMillis`: The handler function should be invoked after time has elapsed") {
    const unsigned long interval = 50;
    Timer t = Timer(callspy::Void);
    t.runMillis(interval);
    World::elapseMillis(interval);
    REQUIRE(callspy::reporter.hasBeenCalled);
    REQUIRE(callspy::reporter.count == 1);
  }

  SECTION("`runMillis`: The handler function should be invoked recurringly") {
    const unsigned long interval = 50;
    Timer t = Timer(callspy::Void);
    t.runMillis(interval);
    World::elapseMillis(3*interval);
    REQUIRE(callspy::reporter.hasBeenCalled);
    REQUIRE(callspy::reporter.count == 3);
  }

  SECTION("`runMillis`: The handler should not be invoked anymore after the timer was stopped") {
    const unsigned long interval = 50;
    Timer t = Timer(callspy::Void);
    t.runMillis(interval);
    World::elapseMillis(3*interval);
    t.stop();
    World::elapseMillis(3*interval);
    REQUIRE(callspy::reporter.count == 3);
  }

  SECTION("`onceMillis`: The handler should not be invoked once after the elapsed time") {
    const unsigned long interval = 50;
    Timer t = Timer(callspy::Void);
    t.onceMillis(interval);
    World::elapseMillis(3*interval);
    REQUIRE(callspy::reporter.hasBeenCalled);
    REQUIRE(callspy::reporter.count == 1);
  }

}
