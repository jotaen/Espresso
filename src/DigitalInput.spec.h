#include <catch.hpp>
#include <Virtuino.h>
#include "DigitalInput.h"

TEST_CASE("[DigitalInput]") {

  callspy::reset();
  Virtuino::clear();

  SECTION("A DigitalInput is a DigitalPin") {
    DigitalInput di(1);
    DigitalPin& d = di; // The “assertion” is that this compiles
  }

  SECTION("It sets the pin mode correctly") {
    DigitalInput di(12);
    REQUIRE(Virtuino::checkPinMode(di.pin()) == INPUT);
  }

  SECTION("The pin mode can optionally be set to `INPUT_PULLUP` as well") {
    DigitalInput di(5, INPUT_PULLUP);
    REQUIRE(Virtuino::checkPinMode(di.pin()) == INPUT_PULLUP);
  }

  SECTION("Pin mode defaults to `INPUT` if funny value is given") {
    DigitalInput di(5, 42);
    REQUIRE(Virtuino::checkPinMode(di.pin()) == INPUT);
  }

  SECTION("The value should be `low` initially") {
    DigitalInput di(2);
    REQUIRE(!di.isHigh());
    REQUIRE(di.isLow());
    REQUIRE(di.value() == LOW);
  }

  SECTION("The value should be `high` according to pin") {
    DigitalInput di(7);
    Virtuino::setDigitalInput(di.pin(), HIGH);
    REQUIRE(di.isHigh());
    REQUIRE(!di.isLow());
    REQUIRE(di.value() == HIGH);
  }

  SECTION("They behave independently from one another") {
    DigitalInput di1(6);
    DigitalInput di2(11);
    Virtuino::setDigitalInput(di2.pin(), HIGH);
    REQUIRE(di1.isLow());
    REQUIRE(di2.isHigh());
  }
}
