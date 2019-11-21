#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "util/fn.h"
#include "Observer.h"
#include "util/CallSpy.h"

bool predicateValue = false;

TEST_CASE("[Observer]") {

  Virtuino::clear();
  CallSpy spy;
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
    o.onTrue(spy.Void);
    Virtuino::elapseMillis(10);
    REQUIRE(spy.hasBeenCalled() == false); // since there was no change so far
    predicateValue = false;
    Virtuino::elapseMillis(10);
    REQUIRE(spy.hasBeenCalled() == false);
    predicateValue = true;
    Virtuino::elapseMillis(10);
    REQUIRE(spy.counter() == 1);
  }

  SECTION("`onTrue` gets called repeatedly (mode=WHILE)") {
    Observer o(fn::alwaysTrue);
    o.onTrue(spy.Void, Observer::WHILE);
    Virtuino::flush();
    REQUIRE(spy.counter() == 1);
    Virtuino::elapseMillis(10);
    REQUIRE(spy.counter() > 2);
  }

  SECTION("`onFalse` gets called once when state changes (mode=ONCE)") {
    Observer o([](){ return predicateValue; });
    o.onFalse(spy.Void);
    Virtuino::elapseMillis(10);
    REQUIRE(spy.hasBeenCalled() == false); // since there was no change so far
    predicateValue = true;
    Virtuino::elapseMillis(10);
    REQUIRE(spy.hasBeenCalled() == false);
    predicateValue = false;
    Virtuino::elapseMillis(10);
    REQUIRE(spy.counter() == 1);
  }

  SECTION("`onFalse` gets called repeatedly (mode=WHILE)") {
    Observer o(fn::alwaysFalse);
    o.onFalse(spy.Void, Observer::WHILE);
    Virtuino::flush();
    REQUIRE(spy.counter() == 1);
    Virtuino::elapseMillis(10);
    REQUIRE(spy.counter() > 2);
  }

  SECTION("For `true`: Only the matching handlers get invoked") {
    Observer o1(fn::alwaysTrue);
    o1.onTrue(spy.Void);
    o1.onFalse([](){ throw; });
    REQUIRE_NOTHROW(Virtuino::flush());

    Observer o2(fn::alwaysFalse);
    o2.onFalse(spy.Void);
    o2.onTrue([](){ throw; });
    REQUIRE_NOTHROW(Virtuino::flush());
  }

  SECTION("Observer can be disabled") {
    Observer o([](){ return predicateValue; });
    o.onTrue(spy.Void);
    o.disable();
    predicateValue = true;
    Virtuino::flush();
    REQUIRE(spy.hasBeenCalled() == false);
    o.onTrue(spy.Void, Observer::WHILE);
    Virtuino::flush();
    REQUIRE(spy.hasBeenCalled() == false);
    REQUIRE(o.isActive() == false);

    o.enable();
    REQUIRE(o.isActive() == true);
    Virtuino::flush();
    REQUIRE(spy.hasBeenCalled());
  }

}
