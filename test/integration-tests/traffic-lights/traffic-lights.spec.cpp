#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "traffic-lights.ino"

Virtuino virtuino;

TEST_CASE("Traffic light is green initially", "[Traffic-Lights]") {
  REQUIRE(red.isLow());
  REQUIRE(yellow.isLow());
  REQUIRE(green.isHigh());
}

TEST_CASE("Traffic light switches to red in correct sequence", "[Traffic-Lights]") {
  REQUIRE(red.isLow());
  REQUIRE(yellow.isLow());
  REQUIRE(green.isHigh());
  virtuino.elapseMillis(5000);
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

TEST_CASE("Traffic light switches to green in correct sequence", "[Traffic-Lights]") {
  REQUIRE(red.isHigh());
  REQUIRE(yellow.isLow());
  REQUIRE(green.isLow());
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

TEST_CASE("Button is deactivated while switching is ongoing", "[Traffic-Lights]") {
  REQUIRE(red.isLow());
  REQUIRE(yellow.isLow());
  REQUIRE(green.isHigh());
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
