#include <catch.hpp>
#include <World.h>
#include "DigitalOutput.h"

TEST_CASE("[DigitalOutput]") {

  callspy::reset();
  World::reset();

  SECTION("It knows its pin number") {
    DigitalOutput dt = DigitalOutput(4);
    REQUIRE(dt.pin() == 4);
  }

  SECTION("By default the value is `LOW`") {
    DigitalOutput dt = DigitalOutput(2);
    REQUIRE(dt.get() == LOW);
    REQUIRE(dt.isLow());
    REQUIRE(!dt.isHigh());
  }

  SECTION("`set` sets the value to HIGH") {
    DigitalOutput dt = DigitalOutput(2);
    dt.set(HIGH);
    REQUIRE(dt.get() == HIGH);
    REQUIRE(!dt.isLow());
    REQUIRE(dt.isHigh());
    REQUIRE(World::checkDigitalOutput(dt.pin()) == HIGH);
  }

  SECTION("`set` sets the value to LOW") {
    DigitalOutput dt = DigitalOutput(2);
    dt.set(HIGH);
    dt.set(LOW);
    REQUIRE(dt.get() == LOW);
    REQUIRE(dt.isLow());
    REQUIRE(!dt.isHigh());
    REQUIRE(World::checkDigitalOutput(dt.pin()) == LOW);
  }

}
