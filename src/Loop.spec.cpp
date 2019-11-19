#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "Loop.h"
#include "util/callspy.h"

TEST_CASE("[Loop]") {

  callspy::reset();
  Virtuino::clear();

  SECTION("A Loop is AutoUpdated") {
    Loop l;
    AutoUpdated& au = l; // The “assertion” is that this compiles
  }

  SECTION("The handler function gets called without further ado") {
    Loop l;
    l.onTrigger(callspy::Void);
    Virtuino::flush();
    REQUIRE(callspy::hasBeenCalled());
  }

  SECTION("If no handler function is given, nothing happens") {
    Loop l;
    REQUIRE_NOTHROW(Virtuino::flush());
  }

  SECTION("Loop can be enabled/disabled") {
    Loop l;
    REQUIRE(l.isActive() == true);
    l.onTrigger(callspy::Void);
    l.disable();
    REQUIRE(l.isActive() == false);
    Virtuino::flush();
    REQUIRE(callspy::hasBeenCalled() == false);
    l.enable();
    REQUIRE(l.isActive() == true);
    Virtuino::flush();
    REQUIRE(callspy::hasBeenCalled());
  }
}
