#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "button-led.ino"

Virtuino virtuino;

TEST_CASE("LED is off in the beginning", "[Button-LED]") {
  REQUIRE(led.isLow());
  virtuino.elapseMillis(duration);
  REQUIRE(led.isLow());
  virtuino.elapseMillis(duration);
  REQUIRE(led.isLow());
}

TEST_CASE("LED is lighten up for 3 seconds when is pressed", "[Button-LED]") {
  virtuino.setDigitalInput(button.pin(), HIGH);
  virtuino.setDigitalInput(button.pin(), LOW);
  REQUIRE(led.isHigh());
  virtuino.elapseMillis(duration);
  REQUIRE(led.isLow());
  virtuino.elapseMillis(duration);
  REQUIRE(led.isLow());
}

TEST_CASE("Keeping the button pressed switches the LED off anyway", "[Button-LED]") {
  virtuino.setDigitalInput(button.pin(), HIGH);
  REQUIRE(led.isHigh());
  virtuino.elapseMillis(duration);
  REQUIRE(led.isLow());
  virtuino.setDigitalInput(button.pin(), LOW);
  virtuino.elapseMillis(duration);
  REQUIRE(led.isLow());
}

TEST_CASE("Pressing the button again extends the duration", "[Button-LED]") {
  virtuino.setDigitalInput(button.pin(), HIGH);
  virtuino.setDigitalInput(button.pin(), LOW);
  REQUIRE(led.isHigh());
  virtuino.elapseMillis(duration * 0.5);
  virtuino.setDigitalInput(button.pin(), HIGH);
  virtuino.setDigitalInput(button.pin(), LOW);
  REQUIRE(led.isHigh());
  virtuino.elapseMillis(duration);
  REQUIRE(led.isLow());
}
