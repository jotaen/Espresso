#include <catch.hpp>
#include "Timer.h"

TEST_CASE("[Timer]") {

  callspy::reset();
  Arduino::clear();

  SECTION("A Timer is a Device") {
    Timer t;
    Device& d = t; // The “assertion” is that this compiles
  }

  SECTION("The handler function should not be invoked without the timer being started") {
    Timer t;
    t.onTrigger(callspy::Void);
    Arduino::flush();
    REQUIRE(callspy::hasBeenCalled() == false);
  }

  SECTION("If there is no handler function, nothing happens") {
    Timer t;
    t.start(10);
    REQUIRE_NOTHROW(Arduino::elapseMillis(11));
    REQUIRE(t.isActive() == false);
  }

  SECTION("`isActive` should inform about the timer status") {
    Timer t;
    REQUIRE(t.isActive() == false);
    t.start(10);
    REQUIRE(t.isActive() == true);
    Arduino::elapseMillis(11);
    REQUIRE(t.isActive() == false);
  }

  SECTION("The handler function should not be invoked before the time is elapsed") {
    Timer t;
    t.onTrigger(callspy::Void);
    t.start(10);
    Arduino::flush();
    REQUIRE(callspy::hasBeenCalled() == false);
    Arduino::elapseMillis(3);
    REQUIRE(callspy::hasBeenCalled() == false);
    Arduino::elapseMillis(3);
    REQUIRE(callspy::hasBeenCalled() == false);
    Arduino::elapseMillis(3);
    REQUIRE(callspy::hasBeenCalled() == false);
    Arduino::elapseMillis(1);
    REQUIRE(callspy::hasBeenCalled());
  }

  SECTION("The handler should only be invoked once after the time has elapsed") {
    Timer t;
    t.onTrigger(callspy::Void);
    t.start(1);
    Arduino::elapseMillis(3);
    REQUIRE(callspy::counter() == 1);
  }

  SECTION("The timer can be cancelled") {
    Timer t;
    t.onTrigger(callspy::Void);
    t.start(10);
    Arduino::elapseMillis(3);
    t.cancel();
    REQUIRE(t.isActive() == false);
    Arduino::elapseMillis(50);
    REQUIRE(callspy::hasBeenCalled() == false);
  }
}
