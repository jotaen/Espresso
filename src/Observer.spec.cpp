#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "util/fn.h"
#include "Observer.h"
#include "util/callspy.h"

bool predicateValue = false;

TEST_CASE("[Observer]") {

  callspy::reset();
  Virtuino::clear();
  predicateValue = false;

  SECTION("An Observer is a Device") {
    Observer o(fn::alwaysTrue);
    Device& d = o; // The “assertion” is that this compiles
  }

  SECTION("Absence of handlers is dealt with gracefully") {
    Observer o([](){ return predicateValue; });
    REQUIRE_NOTHROW(Virtuino::flush());
    predicateValue = true;
    REQUIRE_NOTHROW(Virtuino::flush());
  }

  SECTION("`onTrue` gets called once when state changes") {
    predicateValue = true;
    Observer o([](){ return predicateValue; });
    o.onTrue(callspy::Void);
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false); // since there was no change so far
    predicateValue = false;
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false);
    predicateValue = true;
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::counter() == 1);
  }

  SECTION("`whileTrue` gets called repeatedly") {
    Observer o(fn::alwaysTrue);
    o.whileTrue(callspy::Void);
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled());
    REQUIRE(callspy::counter() > 2);
  }

  SECTION("`onFalse` gets called once") {
    Observer o([](){ return predicateValue; });
    o.onFalse(callspy::Void);
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false); // since there was no change so far
    predicateValue = true;
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false);
    predicateValue = false;
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::counter() == 1);
  }

  SECTION("`whileFalse` gets called repeatedly") {
    Observer o(fn::alwaysFalse);
    o.whileFalse(callspy::Void);
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled());
    REQUIRE(callspy::counter() > 2);
  }

  SECTION("For `true`: Only the matching handlers get invoked") {
    Observer o(fn::alwaysTrue);
    o.onTrue(callspy::Void);
    o.whileTrue(callspy::Void);
    o.onFalse([](){ throw; });
    o.whileFalse([](){ throw; });
    REQUIRE_NOTHROW(Virtuino::flush());
  }

  SECTION("For `false`: Only the matching handlers get invoked") {
    Observer o(fn::alwaysFalse);
    o.onFalse(callspy::Void);
    o.whileFalse(callspy::Void);
    o.onTrue([](){ throw; });
    o.whileTrue([](){ throw; });
    REQUIRE_NOTHROW(Virtuino::flush());
  }

}
