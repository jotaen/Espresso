#include "../lib/catch.hpp"
#include "core.h"
#include "Actor.h"

bool alwaysTrue() { return true; }
bool alwaysFalse() { return false; }
bool hasBeenCalled = false;

TEST_CASE("[Actor]") {

  hasBeenCalled = false;

  SECTION("An Actor is a Device") {
    Actor a = Actor(
      alwaysTrue,
      [](){}
    );
    Device& d = a; // The “assertion” is that this compiles
  }

  SECTION("`onLoop` calls handler when predicate is `true`") {
    Actor a = Actor(
      alwaysTrue,
      [](){ hasBeenCalled = true; }
    );
    _core::callOnLoop(a);
    REQUIRE(hasBeenCalled == true);
  }

  SECTION("`onLoop` doesn’t call handler when predicate is `false`") {
    Actor a = Actor(
      alwaysFalse,
      [](){ hasBeenCalled = true; }
    );
    _core::callOnLoop(a);
    REQUIRE(hasBeenCalled == false);
  }

}
