#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "DigitalOutput.h"
#include "util/CallSpy.h"

TEST_CASE("[DigitalOutput]") {

  Virtuino::clear();

  SECTION("A DigitalOutput is a DigitalPin") {
    DigitalOutput dt(1);
    DigitalPin& d = dt; // The “assertion” is that this compiles
  }

  SECTION("It sets the pin mode correctly") {
    DigitalOutput dt(12);
    REQUIRE(Virtuino::checkPinMode(dt.pin()) == OUTPUT);
  }

  SECTION("By default the value is `LOW`") {
    DigitalOutput dt(2);
    REQUIRE(dt.value() == LOW);
    REQUIRE(dt.isLow());
    REQUIRE(!dt.isHigh());
  }

  SECTION("`write` sets the value to HIGH") {
    DigitalOutput dt(2);
    dt.write(HIGH);
    REQUIRE(dt.value() == HIGH);
    REQUIRE(!dt.isLow());
    REQUIRE(dt.isHigh());
    REQUIRE(Virtuino::checkDigitalOutput(dt.pin()) == HIGH);
  }

  SECTION("`write` sets the value to LOW") {
    DigitalOutput dt(2);
    dt.write(HIGH);
    dt.write(LOW);
    REQUIRE(dt.value() == LOW);
    REQUIRE(dt.isLow());
    REQUIRE(!dt.isHigh());
    REQUIRE(Virtuino::checkDigitalOutput(dt.pin()) == LOW);
  }

  SECTION("`toggle` flips the value") {
    DigitalOutput dt(2);
    dt.write(HIGH);
    dt.toggle();
    REQUIRE(dt.isLow());
    dt.toggle();
    REQUIRE(dt.isHigh());
    dt.toggle();
    REQUIRE(dt.isLow());
  }

}
