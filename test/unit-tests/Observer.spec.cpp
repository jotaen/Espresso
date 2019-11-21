#include "../../src/Observer.h"

bool predicateValue = false;

TEST_CASE("[Observer]") {

  Virtuino virtuino;
  CallSpy spy;
  predicateValue = false;

  SECTION("An Observer is AutoUpdated") {
    Observer o(fn::alwaysTrue);
    AutoUpdated& au = o; // The “assertion” is that this compiles
  }

  SECTION("Absence of handlers is dealt with gracefully") {
    Observer o([](){ return predicateValue; });
    REQUIRE_NOTHROW(virtuino.flush());
    predicateValue = true;
    REQUIRE_NOTHROW(virtuino.flush());
  }

  SECTION("`onTrue` gets called once when state changes (mode=ONCE)") {
    predicateValue = true;
    Observer o([](){ return predicateValue; });
    o.onTrue(spy.Void);
    virtuino.elapseMillis(10);
    REQUIRE(spy.hasBeenCalled() == false); // since there was no change so far
    predicateValue = false;
    virtuino.elapseMillis(10);
    REQUIRE(spy.hasBeenCalled() == false);
    predicateValue = true;
    virtuino.elapseMillis(10);
    REQUIRE(spy.counter() == 1);
  }

  SECTION("`onTrue` gets called repeatedly (mode=WHILE)") {
    Observer o(fn::alwaysTrue);
    o.onTrue(spy.Void, Observer::WHILE);
    virtuino.flush();
    REQUIRE(spy.counter() == 1);
    virtuino.elapseMillis(10);
    REQUIRE(spy.counter() > 2);
  }

  SECTION("`onFalse` gets called once when state changes (mode=ONCE)") {
    Observer o([](){ return predicateValue; });
    o.onFalse(spy.Void);
    virtuino.elapseMillis(10);
    REQUIRE(spy.hasBeenCalled() == false); // since there was no change so far
    predicateValue = true;
    virtuino.elapseMillis(10);
    REQUIRE(spy.hasBeenCalled() == false);
    predicateValue = false;
    virtuino.elapseMillis(10);
    REQUIRE(spy.counter() == 1);
  }

  SECTION("`onFalse` gets called repeatedly (mode=WHILE)") {
    Observer o(fn::alwaysFalse);
    o.onFalse(spy.Void, Observer::WHILE);
    virtuino.flush();
    REQUIRE(spy.counter() == 1);
    virtuino.elapseMillis(10);
    REQUIRE(spy.counter() > 2);
  }

  SECTION("For `true`: Only the matching handlers get invoked") {
    Observer o1(fn::alwaysTrue);
    o1.onTrue(spy.Void);
    o1.onFalse([](){ throw; });
    REQUIRE_NOTHROW(virtuino.flush());

    Observer o2(fn::alwaysFalse);
    o2.onFalse(spy.Void);
    o2.onTrue([](){ throw; });
    REQUIRE_NOTHROW(virtuino.flush());
  }

  SECTION("Observer can be disabled") {
    Observer o([](){ return predicateValue; });
    o.onTrue(spy.Void);
    o.disable();
    predicateValue = true;
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled() == false);
    o.onTrue(spy.Void, Observer::WHILE);
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled() == false);
    REQUIRE(o.isActive() == false);

    o.enable();
    REQUIRE(o.isActive() == true);
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled());
  }

}
