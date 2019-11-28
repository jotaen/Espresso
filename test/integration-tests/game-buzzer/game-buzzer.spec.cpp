#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "game-buzzer.ino"

TEST_CASE("[Game-Buzzer]") {

  Virtuino virtuino(Virtuino::RESET);
  buzzerObserver.enable();
  lightTeam1.write(LOW);
  lightTeam2.write(LOW);

  SECTION("Everything is off in the beginning") {
    REQUIRE(lightTeam1.isLow());
    REQUIRE(lightTeam2.isLow());
    REQUIRE(sound.isLow());
  }

  SECTION("When team 1 buzzers, there is a short sound and the resp. light turns on") {
    virtuino.setDigitalInput(buzzer1.pin(), HIGH);
    virtuino.setDigitalInput(buzzer1.pin(), LOW);
    REQUIRE(sound.isHigh());
    REQUIRE(lightTeam1.isHigh());
    virtuino.elapseMillis(500);
    REQUIRE(sound.isLow());
    REQUIRE(lightTeam1.isHigh());
  }

  SECTION("When team 2 buzzers, there is a short sound and the resp. light turns on") {
    virtuino.setDigitalInput(buzzer2.pin(), HIGH);
    virtuino.setDigitalInput(buzzer2.pin(), LOW);
    REQUIRE(sound.isHigh());
    REQUIRE(lightTeam2.isHigh());
    virtuino.elapseMillis(500);
    REQUIRE(sound.isLow());
    REQUIRE(lightTeam2.isHigh());
  }

  SECTION("When someone had buzzered, the system is locked") {
    virtuino.setDigitalInput(buzzer1.pin(), HIGH);
    virtuino.setDigitalInput(buzzer1.pin(), LOW);
    virtuino.setDigitalInput(buzzer2.pin(), HIGH);
    virtuino.setDigitalInput(buzzer2.pin(), LOW);
    REQUIRE(lightTeam1.isHigh());
    REQUIRE(lightTeam2.isLow());
    virtuino.elapseMillis(500);
    virtuino.setDigitalInput(buzzer1.pin(), HIGH);
    virtuino.setDigitalInput(buzzer1.pin(), LOW);
    REQUIRE(sound.isLow());
    REQUIRE(lightTeam1.isHigh());
    virtuino.setDigitalInput(buzzer2.pin(), HIGH);
    virtuino.setDigitalInput(buzzer2.pin(), LOW);
    REQUIRE(lightTeam2.isLow());
  }

  SECTION("The game master can reset the locked system") {
    virtuino.setDigitalInput(buzzer1.pin(), HIGH);
    virtuino.setDigitalInput(buzzer1.pin(), LOW);
    virtuino.elapseMillis(1000);
    virtuino.setDigitalInput(resetButton.pin(), HIGH);
    virtuino.setDigitalInput(resetButton.pin(), LOW);
    REQUIRE(lightTeam1.isLow());
    REQUIRE(lightTeam2.isLow());
    virtuino.setDigitalInput(buzzer2.pin(), HIGH);
    virtuino.setDigitalInput(buzzer2.pin(), LOW);
    REQUIRE(lightTeam2.isHigh());
  }

}
