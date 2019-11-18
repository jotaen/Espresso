#include <catch.hpp>
#include <fn.h>
#include "Observer.h"

bool predicateValue = false;

TEST_CASE("[Observer]") {

  callspy::reset();
  Arduino::clear();
  predicateValue = false;

  SECTION("An Observer is a Device") {
    Observer o = Observer(fn::alwaysTrue);
    Device& d = o; // The “assertion” is that this compiles
  }

  SECTION("Absence of handlers is dealt with gracefully") {
    Observer o = Observer([](){ return predicateValue; });
    REQUIRE_NOTHROW(Arduino::flush());
    predicateValue = true;
    REQUIRE_NOTHROW(Arduino::flush());
  }

  SECTION("`onTrue` gets called once when state changes") {
    predicateValue = true;
    Observer o = Observer([](){ return predicateValue; });
    o.onTrue(callspy::Void);
    Arduino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false); // since there was no change so far
    predicateValue = false;
    Arduino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false);
    predicateValue = true;
    Arduino::elapseMillis(10);
    REQUIRE(callspy::counter() == 1);
  }

  SECTION("`whileTrue` gets called repeatedly") {
    Observer o = Observer(fn::alwaysTrue);
    o.whileTrue(callspy::Void);
    Arduino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled());
    REQUIRE(callspy::counter() > 2);
  }

  SECTION("`onFalse` gets called once") {
    Observer o = Observer([](){ return predicateValue; });
    o.onFalse(callspy::Void);
    Arduino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false); // since there was no change so far
    predicateValue = true;
    Arduino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false);
    predicateValue = false;
    Arduino::elapseMillis(10);
    REQUIRE(callspy::counter() == 1);
  }

  SECTION("`whileFalse` gets called repeatedly") {
    Observer o = Observer(fn::alwaysFalse);
    o.whileFalse(callspy::Void);
    Arduino::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled());
    REQUIRE(callspy::counter() > 2);
  }

  SECTION("For `true`: Only the matching handlers get invoked") {
    Observer o = Observer(fn::alwaysTrue);
    o.onTrue(callspy::Void);
    o.whileTrue(callspy::Void);
    o.onFalse([](){ throw; });
    o.whileFalse([](){ throw; });
    REQUIRE_NOTHROW(Arduino::flush());
  }

  SECTION("For `false`: Only the matching handlers get invoked") {
    Observer o = Observer(fn::alwaysFalse);
    o.onFalse(callspy::Void);
    o.whileFalse(callspy::Void);
    o.onTrue([](){ throw; });
    o.whileTrue([](){ throw; });
    REQUIRE_NOTHROW(Arduino::flush());
  }

}
