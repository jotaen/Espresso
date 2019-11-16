#include "../lib/catch.hpp"
#include "yps.h"
#include "Timer.h"
#include "utils.h"

TEST_CASE("[Timer]") {

  callspy::reset();

  SECTION("A Timer is a Device") {
    Timer t = Timer(noop);
    Device& d = t; // The “assertion” is that this compiles
  }

  SECTION("The handler function should not be invoked after the time has elapsed") {
    Timer t = Timer(callspy::Void);
    REQUIRE(!callspy::reporter.hasBeenCalled);
  }

}
