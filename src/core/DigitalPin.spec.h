#include <catch.hpp>
#include <Virtuino.h>
#include "DigitalPin.h"

TEST_CASE("[DigitalPin]") {

  Virtuino::clear();

  SECTION("It remembers its pin number") {
    DigitalPin dp(2, INPUT);
    REQUIRE(dp.pin() == 2);
  }

  SECTION("It throws when pin number is invalid") {
    REQUIRE_THROWS(DigitalPin(0, INPUT));
  }

  SECTION("It sets the pin mode correctly") {
    DigitalPin dp(12, INPUT_PULLUP);
    REQUIRE(Virtuino::checkPinMode(dp.pin()) == INPUT_PULLUP);
  }

}
