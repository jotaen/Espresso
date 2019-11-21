#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "blinkbutton.ino"

Virtuino virtuino;

TEST_CASE("LED is off in the beginning", "[BlinkButton]") {
  REQUIRE(led.isLow());
  virtuino.elapseMillis(frequency);
  REQUIRE(led.isLow());
  virtuino.elapseMillis(frequency);
  REQUIRE(led.isLow());
}

TEST_CASE("LED starts blinking while button is pressed", "[BlinkButton]") {
  virtuino.setDigitalInput(button.pin(), HIGH);
  REQUIRE(led.isHigh());
  virtuino.elapseMillis(frequency);
  REQUIRE(led.isLow());
  virtuino.elapseMillis(frequency);
  REQUIRE(led.isHigh());
  virtuino.elapseMillis(frequency);
  REQUIRE(led.isLow());
}

TEST_CASE("LED turns off when button is released", "[BlinkButton]") {
  virtuino.setDigitalInput(button.pin(), LOW);
  REQUIRE(led.isLow());
  virtuino.elapseMillis(frequency);
  REQUIRE(led.isLow());
}
