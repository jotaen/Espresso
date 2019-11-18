#include <catch.hpp>
#include "DigitalInput.h"

TEST_CASE("[DigitalInput]") {

  callspy::reset();
  Arduino::clear();

  SECTION("A DigitalInput is a Device") {
    DigitalInput di(0);
    Device& d = di; // The “assertion” is that this compiles
  }

  SECTION("It knows its pin number") {
    DigitalInput di(7);
    REQUIRE(di.pin() == 7);
  }

  SECTION("It sets the pin mode correctly") {
    DigitalInput di(12);
    REQUIRE(Arduino::checkPinMode(di.pin()) == INPUT);
  }

  SECTION("The pin mode can optionally be set to `INPUT_PULLUP` as well") {
    DigitalInput di(5, INPUT_PULLUP);
    REQUIRE(Arduino::checkPinMode(di.pin()) == INPUT_PULLUP);
  }

  SECTION("Pin mode defaults to `INPUT` if funny value is given") {
    DigitalInput di(5, 42);
    REQUIRE(Arduino::checkPinMode(di.pin()) == INPUT);
  }

  SECTION("The value should be `low` initially") {
    DigitalInput di(2);
    REQUIRE(!di.isHigh());
    REQUIRE(di.isLow());
    REQUIRE(di.value() == LOW);
  }

  SECTION("The value should be `high` according to pin") {
    DigitalInput di(7);
    Arduino::setDigitalInput(di.pin(), HIGH);
    REQUIRE(di.isHigh());
    REQUIRE(!di.isLow());
    REQUIRE(di.value() == HIGH);
  }

  SECTION("They behave independently from one another") {
    DigitalInput di1(6);
    DigitalInput di2(11);
    Arduino::setDigitalInput(di2.pin(), HIGH);
    REQUIRE(di1.isLow());
    REQUIRE(di2.isHigh());
  }
}
