#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "blinkbutton.ino"

TEST_CASE("Setup...", "[BlinkButton]") {
  Arduino::start();
}

TEST_CASE("LED is off in the beginning", "[BlinkButton]") {
  REQUIRE(led.isLow());
  Arduino::elapseMillis(frequency);
  REQUIRE(led.isLow());
  Arduino::elapseMillis(frequency);
  REQUIRE(led.isLow());
}

TEST_CASE("LED starts blinking while button is pressed", "[BlinkButton]") {
  Arduino::setDigitalInput(button.pin(), HIGH);
  REQUIRE(led.isHigh());
  Arduino::elapseMillis(frequency);
  REQUIRE(led.isLow());
  Arduino::elapseMillis(frequency);
  REQUIRE(led.isHigh());
  Arduino::elapseMillis(frequency);
  REQUIRE(led.isLow());
}

TEST_CASE("LED turns off when button is released", "[BlinkButton]") {
  Arduino::setDigitalInput(button.pin(), LOW);
  REQUIRE(led.isLow());
  Arduino::elapseMillis(frequency);
  REQUIRE(led.isLow());
}
