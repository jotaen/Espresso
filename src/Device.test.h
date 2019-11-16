#include "../lib/catch.hpp"
#include "core.h"
#include "Device.h"

TEST_CASE("[Device]") {

  _core::reset();

  SECTION("A single active device points to itself") {
    Device d = Device();
    REQUIRE(_core::next(d) == &d);
  }

  SECTION("Attached devices point to each other subsequent order") {
    Device d1 = Device();
    Device d2 = Device();
    Device d3 = Device();
    REQUIRE(_core::next(d1) == &d2);
    REQUIRE(_core::next(d2) == &d3);
    REQUIRE(_core::next(d3) == &d1);
  }

  SECTION("A detached device is no longer referenced") {
    Device d1 = Device();
    Device d2 = Device();
    {
      Device d3 = Device();
      REQUIRE(_core::next(d1) == &d2);
      REQUIRE(_core::next(d2) == &d3);
      REQUIRE(_core::next(d3) == &d1);
    }
    REQUIRE(_core::next(d1) == &d2);
    REQUIRE(_core::next(d2) == &d1);
  }

  SECTION("Detaching the last (or: only) item cleans up properly") {
    {
      Device d1 = Device();
    }
    Device d2 = Device();
    REQUIRE(_core::next(d2) == &d2);
  }

}
