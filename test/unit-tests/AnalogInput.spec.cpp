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

  SECTION("It should clean up after itself") {
    {
      AnalogInput ai(1);
      ai.update(); // this causes the AI to occupy the ADC
    }
    AnalogInput ai(2);
    virtuino.setAnalogInput(ai.pin(), 15);
    REQUIRE(ai.value() == 15);
  }

  SECTION("The value should be read correctly") {
    AnalogInput ai(1);
    virtuino.setAnalogInput(ai.pin(), 5);
    virtuino.flush();
    REQUIRE(ai.value() == 5);
    virtuino.setAnalogInput(ai.pin(), 68);
    virtuino.flush();
    REQUIRE(ai.value() == 68);
    virtuino.setAnalogInput(ai.pin(), 35);
    virtuino.flush();
    REQUIRE(ai.value() == 35);
  }

  SECTION("Multiple AnalogInputs don’t interfer with each other") {
    AnalogInput ai1(1);
    AnalogInput ai2(2);
    AnalogInput ai3(3);
    virtuino.setAnalogInput(ai1.pin(), 81);
    virtuino.setAnalogInput(ai2.pin(), 31);
    virtuino.setAnalogInput(ai3.pin(), 240);
    REQUIRE(ai1.value() == 81);
    REQUIRE(ai2.value() == 31);
    REQUIRE(ai3.value() == 240);
    virtuino.flush();
    virtuino.setAnalogInput(ai3.pin(), 237);
    REQUIRE(ai3.value() == 237);
    REQUIRE(ai2.value() == 31);
    REQUIRE(ai1.value() == 81);
    virtuino.setAnalogInput(ai2.pin(), 32);
    virtuino.elapseMillis(1);
    REQUIRE(ai1.value() == 81);
    REQUIRE(ai2.value() == 32);
    REQUIRE(ai3.value() == 237);
    virtuino.elapseMillis(2);
    virtuino.setAnalogInput(ai3.pin(), 231);
    REQUIRE(ai2.value() == 32);
    REQUIRE(ai3.value() == 231);
    REQUIRE(ai1.value() == 81);
  }

  SECTION("`valueBlocking` waits for the value") {
    AnalogInput ai1(3);
    AnalogInput ai2(1);
    virtuino.setAnalogInput(ai1.pin(), 81);
    virtuino.setAnalogInput(ai2.pin(), 31);
    REQUIRE(ai1.valueBlocking() == 81);
    virtuino.flush();
    REQUIRE(ai1.valueBlocking() == 81);
    virtuino.flush();
    REQUIRE(ai1.valueBlocking() == 81);
  }
}
