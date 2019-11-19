#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "Timer.h"
#include "util/callspy.h"

TEST_CASE("[Timer]") {

  callspy::reset();
  Virtuino::clear();

  SECTION("A Timer is AutoUpdated") {
    Timer t;
    AutoUpdated& au = t; // The “assertion” is that this compiles
  }

  SECTION("The handler function should not be invoked without the timer being started") {
    Timer t;
    t.onTrigger(callspy::Void);
    Virtuino::flush();
    REQUIRE(callspy::hasBeenCalled() == false);
  }

  SECTION("If there is no handler function, nothing happens") {
    Timer t;
    t.start(10);
    REQUIRE_NOTHROW(Virtuino::elapseMillis(11));
    REQUIRE(t.isActive() == false);
  }

  SECTION("`isActive` should inform about the timer status") {
    Timer t;
    REQUIRE(t.isActive() == false);
    t.start(10);
    REQUIRE(t.isActive() == true);
    Virtuino::elapseMillis(11);
    REQUIRE(t.isActive() == false);
  }

  SECTION("The handler function should not be invoked before the time is elapsed") {
    Timer t;
    t.onTrigger(callspy::Void);
    t.start(10);
    Virtuino::flush();
    REQUIRE(callspy::hasBeenCalled() == false);
    Virtuino::elapseMillis(3);
    REQUIRE(callspy::hasBeenCalled() == false);
    Virtuino::elapseMillis(3);
    REQUIRE(callspy::hasBeenCalled() == false);
    Virtuino::elapseMillis(3);
    REQUIRE(callspy::hasBeenCalled() == false);
    Virtuino::elapseMillis(1);
    REQUIRE(callspy::hasBeenCalled());
  }

  SECTION("The handler should only be invoked once after the time has elapsed") {
    Timer t;
    t.onTrigger(callspy::Void);
    t.start(1);
    Virtuino::elapseMillis(3);
    REQUIRE(callspy::counter() == 1);
  }

  SECTION("The timer can be cancelled") {
    Timer t;
    t.onTrigger(callspy::Void);
    t.start(10);
    Virtuino::elapseMillis(3);
    t.cancel();
    REQUIRE(t.isActive() == false);
    Virtuino::elapseMillis(50);
    REQUIRE(callspy::hasBeenCalled() == false);
  }

  SECTION("`delay` sets and gets the delay value") {
    Timer t;
    t.onTrigger(callspy::Void);
    t.delay(50);
    REQUIRE(t.delay() == 50);
    Virtuino::elapseMillis(30); // make sure `delay` doesn’t set other internal state
    t.start();
    Virtuino::elapseMillis(49);
    REQUIRE(callspy::hasBeenCalled() == false);
    Virtuino::elapseMillis(1);
    REQUIRE(callspy::hasBeenCalled());
  }

  SECTION("Calling `delay` on a running timer resets the value after the fact") {
    Timer t;
    t.onTrigger(callspy::Void);
    t.start(10);
    Virtuino::elapseMillis(9);
    t.delay(20);
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false);
    Virtuino::elapseMillis(1);
    REQUIRE(callspy::hasBeenCalled());
  }

  SECTION("Calling `start()` or `start(long)` restarts the timer") {
    Timer t;
    t.onTrigger(callspy::Void);
    t.start(10);
    Virtuino::elapseMillis(9);
    t.start();
    Virtuino::elapseMillis(9);
    t.start(20);
    Virtuino::elapseMillis(19);
    t.start(30);
    Virtuino::elapseMillis(29);
    REQUIRE(callspy::hasBeenCalled() == false);
    Virtuino::elapseMillis(2);
    REQUIRE(callspy::hasBeenCalled());
  }
}
