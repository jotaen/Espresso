#include <catch.hpp>
#include "DigitalInput.h"

TEST_CASE("[DigitalInput]") {

  callspy::reset();
  Arduino::clear();

  SECTION("A DigitalInput is a Device") {
    DigitalInput di = DigitalInput(0);
    Device& d = di; // The “assertion” is that this compiles
  }

  SECTION("It knows its pin number") {
    DigitalInput di = DigitalInput(7);
    REQUIRE(di.pin() == 7);
  }

  SECTION("It sets the pin mode correctly") {
    DigitalInput di = DigitalInput(12);
    REQUIRE(Arduino::checkPinMode(di.pin()) == INPUT);
  }

  SECTION("The value should be `low` initially") {
    DigitalInput di = DigitalInput(2);
    REQUIRE(!di.isHigh());
    REQUIRE(di.isLow());
    REQUIRE(di.value() == LOW);
  }

  SECTION("The value should be `high` according to pin") {
    DigitalInput di = DigitalInput(7);
    Arduino::setDigitalInput(di.pin(), HIGH);
    REQUIRE(di.isHigh());
    REQUIRE(!di.isLow());
    REQUIRE(di.value() == HIGH);
  }

  SECTION("They behave independently from one another") {
    DigitalInput di1 = DigitalInput(6);
    DigitalInput di2 = DigitalInput(11);
    Arduino::setDigitalInput(di2.pin(), HIGH);
    REQUIRE(di1.isLow());
    REQUIRE(di2.isHigh());
  }
}
