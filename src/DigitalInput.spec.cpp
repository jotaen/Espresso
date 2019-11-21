#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "DigitalInput.h"

TEST_CASE("[DigitalInput]") {

  Virtuino virtuino;

  SECTION("A DigitalInput is a DigitalPin") {
    DigitalInput di(1);
    DigitalPin& d = di; // The “assertion” is that this compiles
  }

  SECTION("It defaults the pin mode to `INPUT`") {
    DigitalInput di(12);
    REQUIRE(virtuino.checkPinMode(di.pin()) == INPUT);
  }

  SECTION("The pin mode can optionally be set to `INPUT_PULLUP` as well") {
    DigitalInput di(5, INPUT_PULLUP);
    REQUIRE(virtuino.checkPinMode(di.pin()) == INPUT_PULLUP);
  }

  SECTION("It throws when pin mode is invalid") {
    REQUIRE_THROWS(DigitalInput(8, 172)); // `172` is never valid for mode
  }

  SECTION("The value should be `low` initially") {
    DigitalInput di(2);
    REQUIRE(!di.isHigh());
    REQUIRE(di.isLow());
    REQUIRE(di.value() == LOW);
  }

  SECTION("The value should be `high` according to pin") {
    DigitalInput di(7);
    virtuino.setDigitalInput(di.pin(), HIGH);
    REQUIRE(di.isHigh());
    REQUIRE(!di.isLow());
    REQUIRE(di.value() == HIGH);
  }

  SECTION("They behave independently from one another") {
    DigitalInput di1(6);
    DigitalInput di2(11);
    virtuino.setDigitalInput(di2.pin(), HIGH);
    REQUIRE(di1.isLow());
    REQUIRE(di2.isHigh());
  }
}
