#include "../../src/AnalogInput.h"

TEST_CASE("[AnalogInput]") {

  Virtuino virtuino(Virtuino::DESTROY);

  SECTION("An AnalogInput is `AutoUpdated`") {
    AnalogInput ai(1);
    AutoUpdated& d = ai; // The “assertion” is that this compiles
  }

  SECTION("It remembers its pin value") {
    AnalogInput ai(3);
    REQUIRE(ai.pin() == 3);
  }

  SECTION("The value should be `0` initially") {
    AnalogInput ai(2);
    REQUIRE(ai.value() == 0);
  }

  SECTION("The value be according to pin value") {
    AnalogInput ai(1);
    virtuino.setAnalogInput(ai.pin(), 5);
    virtuino.elapseMillis(1);
    REQUIRE(ai.value() == 5);
    virtuino.setAnalogInput(ai.pin(), 68);
    virtuino.elapseMillis(1);
    REQUIRE(ai.value() == 68);
    virtuino.setAnalogInput(ai.pin(), 35);
    virtuino.elapseMillis(1);
    REQUIRE(ai.value() == 35);
  }

  SECTION("Two AnalogInputs don’t interfer") {
    AnalogInput ai1(3);
    AnalogInput ai2(1);
    virtuino.setAnalogInput(ai1.pin(), 81);
    virtuino.setAnalogInput(ai2.pin(), 31);
    virtuino.elapseMillis(1);
    REQUIRE(ai1.value() == 81);
    virtuino.elapseMillis(1);
    REQUIRE(ai2.value() == 31);
    virtuino.elapseMillis(5);
    REQUIRE(ai1.value() == 81);
    REQUIRE(ai2.value() == 31);
  }
}
