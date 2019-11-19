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

  SECTION("An Observer is AutoUpdated") {
    Observer o(fn::alwaysTrue);
    AutoUpdated& au = o; // The “assertion” is that this compiles
  }

  SECTION("Absence of handlers is dealt with gracefully") {
    Observer o([](){ return predicateValue; });
    REQUIRE_NOTHROW(Virtuino::flush());
    predicateValue = true;
    REQUIRE_NOTHROW(Virtuino::flush());
  }

  SECTION("`onTrue` gets called once when state changes (mode=ONCE)") {
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

  SECTION("`onTrue` gets called repeatedly (mode=WHILE)") {
    Observer o(fn::alwaysTrue);
    o.onTrue(callspy::Void, Observer::WHILE);
    Virtuino::flush();
    REQUIRE(callspy::counter() == 1);
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::counter() > 2);
  }

  SECTION("`onFalse` gets called once when state changes (mode=ONCE)") {
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

  SECTION("`onFalse` gets called repeatedly (mode=WHILE)") {
    Observer o(fn::alwaysFalse);
    o.onFalse(callspy::Void, Observer::WHILE);
    Virtuino::flush();
    REQUIRE(callspy::counter() == 1);
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::counter() > 2);
  }

  SECTION("For `true`: Only the matching handlers get invoked") {
    Observer o(fn::alwaysTrue);
    o.onTrue(callspy::Void);
    o.onFalse([](){ throw; });
    REQUIRE_NOTHROW(Virtuino::flush());
  }

  SECTION("For `false`: Only the matching handlers get invoked") {
    Observer o(fn::alwaysFalse);
    o.onFalse(callspy::Void);
    o.onTrue([](){ throw; });
    REQUIRE_NOTHROW(Virtuino::flush());
  }

}
