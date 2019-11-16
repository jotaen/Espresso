#include "../lib/catch.hpp"
#include "yps.h"
#include "Actor.h"

bool alwaysTrue() { return true; }
bool alwaysFalse() { return false; }
void noop() {}
bool hasBeenCalled = false;

TEST_CASE("[Actor]") {

  hasBeenCalled = false;

  SECTION("An Actor is a Device") {
    Actor a = Actor(alwaysTrue, noop);
    Device& d = a; // The “assertion” is that this compiles
  }

  SECTION("`onLoop` calls handler when predicate is `true`") {
    Actor a = Actor(alwaysTrue, [](){ hasBeenCalled = true; });
    yps::callOnLoop(a);
    REQUIRE(hasBeenCalled == true);
  }

  SECTION("`onLoop` doesn’t call handler when predicate is `false`") {
    Actor a = Actor(alwaysFalse, [](){ hasBeenCalled = true; });
    yps::callOnLoop(a);
    REQUIRE(hasBeenCalled == false);
  }

}
