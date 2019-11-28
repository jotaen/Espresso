#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "debouncing.ino"

TEST_CASE("[Debouncing]") {

  Virtuino virtuino(Virtuino::RESET);
  triggerCount = 0;

  SECTION("A flickering (bouncing) input signal is ignored") {
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.elapseMillis(debounceTime - 1);
    REQUIRE(triggerCount == 0);
    virtuino.elapseMillis(1);
    REQUIRE(triggerCount == 1);
  }

  SECTION("It doesn’t trigger when the signal does not stabilise") {
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    virtuino.elapseMillis(2 * debounceTime);
    REQUIRE(triggerCount == 0);
  }

}
