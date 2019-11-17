#include <catch.hpp>
#include "DigitalOutput.h"

TEST_CASE("[DigitalOutput]") {

  callspy::reset();
  Arduino::clear();

  SECTION("It knows its pin number") {
    DigitalOutput dt = DigitalOutput(4);
    REQUIRE(dt.pin() == 4);
  }

  SECTION("It sets the pin mode correctly") {
    DigitalOutput dt = DigitalOutput(12);
    REQUIRE(Arduino::checkPinMode(dt.pin()) == OUTPUT);
  }

  SECTION("By default the value is `LOW`") {
    DigitalOutput dt = DigitalOutput(2);
    REQUIRE(dt.value() == LOW);
    REQUIRE(dt.isLow());
    REQUIRE(!dt.isHigh());
  }

  SECTION("`write` sets the value to HIGH") {
    DigitalOutput dt = DigitalOutput(2);
    dt.write(HIGH);
    REQUIRE(dt.value() == HIGH);
    REQUIRE(!dt.isLow());
    REQUIRE(dt.isHigh());
    REQUIRE(Arduino::checkDigitalOutput(dt.pin()) == HIGH);
  }

  SECTION("`write` sets the value to LOW") {
    DigitalOutput dt = DigitalOutput(2);
    dt.write(HIGH);
    dt.write(LOW);
    REQUIRE(dt.value() == LOW);
    REQUIRE(dt.isLow());
    REQUIRE(!dt.isHigh());
    REQUIRE(Arduino::checkDigitalOutput(dt.pin()) == LOW);
  }

  SECTION("`toggle` flips the value") {
    DigitalOutput dt = DigitalOutput(2);
    dt.write(HIGH);
    dt.toggle();
    REQUIRE(dt.isLow());
    dt.toggle();
    REQUIRE(dt.isHigh());
    dt.toggle();
    REQUIRE(dt.isLow());
  }

}
