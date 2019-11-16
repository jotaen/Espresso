#include "../lib/catch.hpp"
#include "yps.h"
#include "Timer.h"

TEST_CASE("[Timer]") {

  yps::reset();

  SECTION("A Timer is a Device") {
    Timer t = Timer();
    Device& d = t; // The “assertion” is that this compiles
  }

}
