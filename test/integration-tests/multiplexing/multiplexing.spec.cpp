#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "multiplexing.ino"

TEST_CASE("[Multiplexing]") {

  Virtuino virtuino(Virtuino::RESET);

  SECTION("You can input a number") {
    // Press `2`:
    virtuino.setDigitalInput(row1.pin(), HIGH);
    virtuino.setDigitalInput(col2.pin(), HIGH);
    virtuino.setDigitalInput(row1.pin(), LOW);
    virtuino.setDigitalInput(col2.pin(), LOW);

    // Press `4`:
    virtuino.setDigitalInput(row2.pin(), HIGH);
    virtuino.setDigitalInput(col1.pin(), HIGH);
    virtuino.setDigitalInput(row2.pin(), LOW);
    virtuino.setDigitalInput(col1.pin(), LOW);

    // Press `9`:
    virtuino.setDigitalInput(row3.pin(), HIGH);
    virtuino.setDigitalInput(col3.pin(), HIGH);
    virtuino.setDigitalInput(row3.pin(), LOW);
    virtuino.setDigitalInput(col3.pin(), LOW);

    REQUIRE(number == "249");
  }

}
