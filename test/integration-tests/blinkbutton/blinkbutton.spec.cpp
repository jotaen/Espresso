#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <World.h>

#include "blinkbutton.ino"

TEST_CASE("LED starts blinking while button is pressed", "[BlinkButton]") {
  World::setDigitalInput(button.pin(), HIGH);
  REQUIRE(led.isHigh());
  World::elapseMillis(frequency);
  REQUIRE(led.isLow());
  World::elapseMillis(frequency);
  REQUIRE(led.isHigh());
  World::elapseMillis(frequency);
  REQUIRE(led.isLow());
}

TEST_CASE("LED turns off when button is released", "[BlinkButton]") {
  World::setDigitalInput(4, LOW);
  REQUIRE(led.isLow());
}
