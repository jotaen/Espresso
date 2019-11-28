#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "button-led.ino"

TEST_CASE("[Button-LED]") {

  Virtuino virtuino(Virtuino::RESET);
  
  SECTION("LED is off in the beginning") {
    REQUIRE(led.isLow());
    virtuino.elapseMillis(duration);
    REQUIRE(led.isLow());
    virtuino.elapseMillis(duration);
    REQUIRE(led.isLow());
  }

  SECTION("LED is lighten up for 3 seconds when is pressed") {
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    REQUIRE(led.isHigh());
    virtuino.elapseMillis(duration);
    REQUIRE(led.isLow());
    virtuino.elapseMillis(duration);
    REQUIRE(led.isLow());
  }

  SECTION("Keeping the button pressed switches the LED off anyway") {
    virtuino.setDigitalInput(button.pin(), HIGH);
    REQUIRE(led.isHigh());
    virtuino.elapseMillis(duration);
    REQUIRE(led.isLow());
    virtuino.setDigitalInput(button.pin(), LOW);
    virtuino.elapseMillis(duration);
    REQUIRE(led.isLow());
  }

  SECTION("Pressing the button again extends the duration") {
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
}
