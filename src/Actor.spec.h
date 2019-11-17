#include <catch.hpp>
#include <World.h>
#include <utils.h>
#include "Actor.h"

bool predicateValue = false;

TEST_CASE("[Actor]") {

  callspy::reset();
  World::destroy();
  predicateValue = false;

  SECTION("An Actor is a Device") {
    Actor a = Actor(alwaysTrue);
    Device& d = a; // The “assertion” is that this compiles
  }

  SECTION("Absence of handlers is dealt with gracefully") {
    Actor a = Actor([](){ return predicateValue; });
    REQUIRE_NOTHROW(World::flush());
    predicateValue = true;
    REQUIRE_NOTHROW(World::flush());
  }

  SECTION("`onTrue` gets called once when state changes") {
    predicateValue = true;
    Actor a = Actor([](){ return predicateValue; });
    a.onTrue(callspy::Void);
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
    Actor a = Actor(alwaysTrue);
    a.whileTrue(callspy::Void);
    World::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled());
    REQUIRE(callspy::counter() > 2);
  }

  SECTION("`onFalse` gets called once") {
    Actor a = Actor([](){ return predicateValue; });
    a.onFalse(callspy::Void);
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
    Actor a = Actor(alwaysFalse);
    a.whileFalse(callspy::Void);
    World::elapseMillis(10);
    REQUIRE(callspy::hasBeenCalled());
    REQUIRE(callspy::counter() > 2);
  }

  SECTION("For `true`: Only the matching handlers get invoked") {
    Actor a = Actor(alwaysTrue);
    a.onTrue(callspy::Void);
    a.whileTrue(callspy::Void);
    a.onFalse([](){ throw; });
    a.whileFalse([](){ throw; });
    REQUIRE_NOTHROW(World::flush());
  }

  SECTION("For `false`: Only the matching handlers get invoked") {
    Actor a = Actor(alwaysFalse);
    a.onFalse(callspy::Void);
    a.whileFalse(callspy::Void);
    a.onTrue([](){ throw; });
    a.whileTrue([](){ throw; });
    REQUIRE_NOTHROW(World::flush());
  }

}
