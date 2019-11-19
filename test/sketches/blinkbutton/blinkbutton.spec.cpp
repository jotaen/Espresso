#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "blinkbutton.ino"

TEST_CASE("Setup...", "[BlinkButton]") {
  Virtuino::start();
}

TEST_CASE("LED is off in the beginning", "[BlinkButton]") {
  REQUIRE(led.isLow());
  Virtuino::elapseMillis(frequency);
  REQUIRE(led.isLow());
  Virtuino::elapseMillis(frequency);
  REQUIRE(led.isLow());
}

TEST_CASE("LED starts blinking while button is pressed", "[BlinkButton]") {
  Virtuino::setDigitalInput(button.pin(), HIGH);
  REQUIRE(led.isHigh());
  Virtuino::elapseMillis(frequency);
  REQUIRE(led.isLow());
  Virtuino::elapseMillis(frequency);
  REQUIRE(led.isHigh());
  Virtuino::elapseMillis(frequency);
  REQUIRE(led.isLow());
}

TEST_CASE("LED turns off when button is released", "[BlinkButton]") {
  Virtuino::setDigitalInput(button.pin(), LOW);
  REQUIRE(led.isLow());
  Virtuino::elapseMillis(frequency);
  REQUIRE(led.isLow());
}
