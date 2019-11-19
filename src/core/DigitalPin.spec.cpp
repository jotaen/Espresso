#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "DigitalPin.h"
#include "../util/callspy.h"

class DigitalPin_: public DigitalPin {
public:
  DigitalPin_(uint8_t pin)
  : DigitalPin(pin) {}
};

TEST_CASE("[DigitalPin]") {

  Virtuino::clear();

  SECTION("It remembers its pin number") {
    DigitalPin_ dp(2);
    REQUIRE(dp.pin() == 2);
  }

  SECTION("It throws when pin number is invalid") {
    REQUIRE_THROWS(DigitalPin_(0)); // `0` is never valid
  }

}
