#include "../lib/catch.hpp"
#include "yps.h"
#include "Actor.h"
#include "utils.h"

TEST_CASE("[Actor]") {

  callspy::reset();

  SECTION("An Actor is a Device") {
    Actor a = Actor(alwaysTrue, noop);
    Device& d = a; // The “assertion” is that this compiles
  }

  SECTION("`onLoop` calls handler when predicate is `true`") {
    Actor a = Actor(alwaysTrue, callspy::Void);
    yps::callOnLoop(a);
    REQUIRE(callspy::reporter.hasBeenCalled);
  }

  SECTION("`onLoop` doesn’t call handler when predicate is `false`") {
    Actor a = Actor(alwaysFalse, callspy::Void);
    yps::callOnLoop(a);
    REQUIRE(!callspy::reporter.hasBeenCalled);
  }

}
