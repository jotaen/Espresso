#include <catch.hpp>
#include <World.h>
#include <utils.h>
#include "Observer.h"

bool predicateValue = false;

TEST_CASE("[Observer]") {

  callspy::reset();
  World::destroy();
  predicateValue = false;

  SECTION("An Observer is a Device") {
    Observer o = Observer(alwaysTrue);
    Device& d = o; // The “assertion” is that this compiles
  }

  SECTION("Absence of handlers is dealt with gracefully") {
    Observer o = Observer([](){ return predicateValue; });
    REQUIRE_NOTHROW(World::flush());
    predicateValue = true;
    REQUIRE_NOTHROW(World::flush());
  }

  SECTION("`onTrue` gets called once when state changes") {
    predicateValue = true;
    Observer o = Observer([](){ return predicateValue; });
    o.onTrue(callspy::Void);
    World::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false); // since there was no change so far
    predicateValue = false;
    World::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false);
    predicateValue = true;
    World::elapseMillis(10);
    REQUIRE(callspy::counter() == 1);
  }

  SECTION("`whileTrue` gets called repeatedly") {
    Observer o = Observer(alwaysTrue);
    o.whileTrue(callspy::Void);
    World::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled());
    REQUIRE(callspy::counter() > 2);
  }

  SECTION("`onFalse` gets called once") {
    Observer o = Observer([](){ return predicateValue; });
    o.onFalse(callspy::Void);
    World::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false); // since there was no change so far
    predicateValue = true;
    World::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled() == false);
    predicateValue = false;
    World::elapseMillis(10);
    REQUIRE(callspy::counter() == 1);
  }

  SECTION("`whileFalse` gets called repeatedly") {
    Observer o = Observer(alwaysFalse);
    o.whileFalse(callspy::Void);
    World::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled());
    REQUIRE(callspy::counter() > 2);
  }

  SECTION("For `true`: Only the matching handlers get invoked") {
    Observer o = Observer(alwaysTrue);
    o.onTrue(callspy::Void);
    o.whileTrue(callspy::Void);
    o.onFalse([](){ throw; });
    o.whileFalse([](){ throw; });
    REQUIRE_NOTHROW(World::flush());
  }

  SECTION("For `false`: Only the matching handlers get invoked") {
    Observer o = Observer(alwaysFalse);
    o.onFalse(callspy::Void);
    o.whileFalse(callspy::Void);
    o.onTrue([](){ throw; });
    o.whileTrue([](){ throw; });
    REQUIRE_NOTHROW(World::flush());
  }

}
