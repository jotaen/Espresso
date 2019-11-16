#include "../test.h"
#include "DigitalInput.h"

TEST_CASE("[DigitalInput]") {

  callspy::reset();
  World::reset();

  SECTION("A DigitalInput is a Device") {
    DigitalInput di = DigitalInput();
    Device& d = di; // The “assertion” is that this compiles
  }

  SECTION("The value is `low` initially") {
    DigitalInput di = DigitalInput();
    REQUIRE(!di.isHigh());
    REQUIRE(di.isLow());
  }
}
