#include "../lib/catch.hpp"
#include "yps.h"
#include "Device.h"

class TestDevice: public Device {
protected:
  void onLoop() {}
};

TEST_CASE("[Device]") {

  yps::reset();

  SECTION("A single active device points to itself") {
    TestDevice d = TestDevice();
    REQUIRE(yps::next(d) == &d);
  }

  SECTION("Devices point to each other subsequent order") {
    TestDevice d1 = TestDevice();
    TestDevice d2 = TestDevice();
    TestDevice d3 = TestDevice();
    REQUIRE(yps::next(d1) == &d2);
    REQUIRE(yps::next(d2) == &d3);
    REQUIRE(yps::next(d3) == &d1);
  }

  SECTION("A destroyed device is no longer referenced") {
    TestDevice d1 = TestDevice();
    TestDevice d2 = TestDevice();
    {
      TestDevice d3 = TestDevice();
      REQUIRE(yps::next(d1) == &d2);
      REQUIRE(yps::next(d2) == &d3);
      REQUIRE(yps::next(d3) == &d1);
    }
    REQUIRE(yps::next(d1) == &d2);
    REQUIRE(yps::next(d2) == &d1);
  }

  SECTION("Destroying the last (or: only) item cleans up properly") {
    {
      TestDevice d1 = TestDevice();
    }
    TestDevice d2 = TestDevice();
    REQUIRE(yps::next(d2) == &d2);
  }

}
