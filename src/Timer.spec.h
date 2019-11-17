#include <catch.hpp>
#include <World.h>
#include <utils.h>
#include "Timer.h"

TEST_CASE("[Timer]") {

  callspy::reset();
  World::reset();

  SECTION("A Timer is a Device") {
    Timer t = Timer(noop);
    Device& d = t; // The “assertion” is that this compiles
  }

  SECTION("The handler function should not be invoked without the timer being started") {
    Timer t = Timer(callspy::Void);
    World::loopOnce();
    REQUIRE(!callspy::reporter.hasBeenCalled);
  }

  SECTION("`isActive` should inform about the timer status") {
    Timer t = Timer(noop);
    REQUIRE(t.isActive() == false);
    t.start(10);
    REQUIRE(t.isActive() == true);
    World::elapseMillis(11);
    REQUIRE(t.isActive() == false);
  }

  SECTION("The handler function should not be invoked before the time is elapsed") {
    Timer t = Timer(callspy::Void);
    t.start(10);
    World::loopOnce();
    REQUIRE(callspy::reporter.hasBeenCalled == false);
    World::elapseMillis(3);
    REQUIRE(callspy::reporter.hasBeenCalled == false);
    World::elapseMillis(3);
    REQUIRE(callspy::reporter.hasBeenCalled == false);
    World::elapseMillis(3);
    REQUIRE(callspy::reporter.hasBeenCalled == false);
    World::elapseMillis(1);
    REQUIRE(callspy::reporter.hasBeenCalled);
  }

  SECTION("The handler should only be invoked once after the time has elapsed") {
    Timer t = Timer(callspy::Void);
    t.start(1);
    World::elapseMillis(3);
    REQUIRE(callspy::reporter.count == 1);
  }

  SECTION("The timer can be cancelled") {
    Timer t = Timer(callspy::Void);
    t.start(10);
    World::elapseMillis(3);
    t.cancel();
    World::elapseMillis(50);
    REQUIRE(callspy::reporter.hasBeenCalled == false);
  }
}
