#include "../test.h"
#include "DigitalInput.h"

TEST_CASE("[DigitalInput]") {

  callspy::reset();
  World::reset();

  SECTION("A DigitalInput is a Device") {
    DigitalInput di = DigitalInput(0);
    Device& d = di; // The “assertion” is that this compiles
  }

  SECTION("The value should be `low` initially") {
    DigitalInput di = DigitalInput(2);
    REQUIRE(!di.isHigh());
    REQUIRE(di.isLow());
    REQUIRE(di.value() == LOW);
  }

  SECTION("The value should be `high` according to pin") {
    const uint8_t pin = 7;
    DigitalInput di = DigitalInput(pin);
    World::setDigitalInput(pin, HIGH);
    REQUIRE(di.isHigh());
    REQUIRE(!di.isLow());
    REQUIRE(di.value() == HIGH);
  }

  SECTION("They behave independently from one another") {
    const uint8_t pin1 = 7;
    const uint8_t pin2 = 12;
    DigitalInput di1 = DigitalInput(pin1);
    DigitalInput di2 = DigitalInput(pin2);
    World::setDigitalInput(pin2, HIGH);
    REQUIRE(di1.isLow());
    REQUIRE(di2.isHigh());
  }
}
