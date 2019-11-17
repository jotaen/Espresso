#include <catch.hpp>
#include <World.h>
#include <utils.h>
#include "Actor.h"

TEST_CASE("[Actor]") {

  callspy::reset();
  World::destroy();

  SECTION("An Actor is a Device") {
    Actor a = Actor(alwaysTrue, noop);
    Device& d = a; // The “assertion” is that this compiles
  }

  SECTION("`onLoop` calls handler when predicate is `true`") {
    Actor a = Actor(alwaysTrue, callspy::Void);
    World::loopOnce();
    REQUIRE(callspy::reporter.hasBeenCalled);
  }

  SECTION("`onLoop` doesn’t call handler when predicate is `false`") {
    Actor a = Actor(alwaysFalse, callspy::Void);
    World::loopOnce();
    REQUIRE(!callspy::reporter.hasBeenCalled);
  }

}
