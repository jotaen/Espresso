#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "blinker.ino"

Virtuino virtuino;

TEST_CASE("It converts an analog value to a value range", "[interval]") {
  REQUIRE(interval(0) == 100);
  REQUIRE(interval(127) == 548);
  REQUIRE(interval(255) == 1000);
}

TEST_CASE("LED blinks according to poti value", "[Blinker]") {
  virtuino.setAnalogInput(poti.pin(), 255);
  REQUIRE(led.isHigh());
  virtuino.elapseMillis(1000);
  REQUIRE(led.isLow());
  virtuino.elapseMillis(1000);
  REQUIRE(led.isHigh());
  virtuino.elapseMillis(1000);
  REQUIRE(led.isLow());
  virtuino.setAnalogInput(poti.pin(), 127);
  virtuino.elapseMillis(550);
  REQUIRE(led.isHigh());

}
