#include <catch.hpp>
#include <World.h>
#include "DigitalOutput.h"

TEST_CASE("[DigitalOutput]") {

  callspy::reset();
  World::destroy();

  SECTION("It knows its pin number") {
    DigitalOutput dt = DigitalOutput(4);
    REQUIRE(dt.pin() == 4);
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
    REQUIRE(World::checkDigitalOutput(dt.pin()) == HIGH);
  }

  SECTION("`write` sets the value to LOW") {
    DigitalOutput dt = DigitalOutput(2);
    dt.write(HIGH);
    dt.write(LOW);
    REQUIRE(dt.value() == LOW);
    REQUIRE(dt.isLow());
    REQUIRE(!dt.isHigh());
    REQUIRE(World::checkDigitalOutput(dt.pin()) == LOW);
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