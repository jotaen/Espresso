#include "../../src/AnalogOutput.h"

TEST_CASE("[AnalogOutput]") {

  Virtuino virtuino(Virtuino::DESTROY);

  SECTION("An AnalogOutput is a DigitalPin") {
    AnalogOutput ao(1);
    DigitalPin& d = ao; // The “assertion” is that this compiles
  }

  SECTION("It sets the pin mode correctly") {
    AnalogOutput ao(12);
    REQUIRE(virtuino.checkPinMode(ao.pin()) == OUTPUT);
  }

  SECTION("By default the value is 0") {
    AnalogOutput ao(2);
    REQUIRE(ao.value() == 0);
  }

  SECTION("`write` sets the value") {
    const int value = 62;
    AnalogOutput ao(2);
    ao.write(value);
    REQUIRE(ao.value() == value);
    REQUIRE(virtuino.checkAnalogOutput(ao.pin()) == value);
  }

}
