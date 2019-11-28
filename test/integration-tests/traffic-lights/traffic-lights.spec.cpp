#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "traffic-lights.ino"

TEST_CASE("[Traffic-Lights]") {

  Virtuino virtuino(Virtuino::RESET);

  SECTION("Traffic light is green initially") {
    REQUIRE(red.isLow());
    REQUIRE(yellow.isLow());
    REQUIRE(green.isHigh());
  }

  SECTION("Traffic light switches to red in correct sequence") {
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    REQUIRE(red.isLow());
    REQUIRE(yellow.isHigh());
    REQUIRE(green.isLow());
    virtuino.elapseMillis(1000);
    REQUIRE(red.isHigh());
    REQUIRE(yellow.isLow());
    REQUIRE(green.isLow());
  }

  SECTION("Traffic light switches to green in correct sequence") {
    // Set to red first
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    virtuino.elapseMillis(5000);

    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    REQUIRE(red.isHigh());
    REQUIRE(yellow.isHigh());
    REQUIRE(green.isLow());
    virtuino.elapseMillis(1000);
    REQUIRE(red.isLow());
    REQUIRE(yellow.isLow());
    REQUIRE(green.isHigh());
  }

  SECTION("Button is deactivated while switching is in progress") {
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    REQUIRE(red.isLow());
    REQUIRE(yellow.isHigh());
    REQUIRE(green.isLow());
    virtuino.elapseMillis(900);
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    virtuino.elapseMillis(100);
    REQUIRE(red.isHigh());
    REQUIRE(yellow.isLow());
    REQUIRE(green.isLow());
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    REQUIRE(red.isHigh());
    REQUIRE(yellow.isHigh());
    REQUIRE(green.isLow());
    virtuino.elapseMillis(900);
    virtuino.setDigitalInput(button.pin(), HIGH);
    virtuino.setDigitalInput(button.pin(), LOW);
    virtuino.elapseMillis(100);
    REQUIRE(red.isLow());
    REQUIRE(yellow.isLow());
    REQUIRE(green.isHigh());
  }

}
