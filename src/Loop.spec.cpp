#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "Loop.h"
#include "util/CallSpy.h"

TEST_CASE("[Loop]") {

  CallSpy spy;
  Virtuino virtuino;

  SECTION("A Loop is AutoUpdated") {
    Loop l;
    AutoUpdated& au = l; // The “assertion” is that this compiles
  }

  SECTION("The handler function gets called without further ado") {
    Loop l;
    l.onTrigger(spy.Void);
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled());
  }

  SECTION("If no handler function is given, nothing happens") {
    Loop l;
    REQUIRE_NOTHROW(virtuino.flush());
  }

  SECTION("Loop can be enabled/disabled") {
    Loop l;
    REQUIRE(l.isActive() == true);
    l.onTrigger(spy.Void);
    l.disable();
    REQUIRE(l.isActive() == false);
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled() == false);
    l.enable();
    REQUIRE(l.isActive() == true);
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled());
  }
}
