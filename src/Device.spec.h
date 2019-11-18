#include <catch.hpp>
#include "Device.h"

class TestDevice: public Device {
protected:
  void onLoop() {}
};

TEST_CASE("[Device]") {

  Arduino::clear();

  SECTION("A single active device points to itself") {
    TestDevice d = TestDevice();
    REQUIRE(Device::next(d) == &d);
  }

  SECTION("Devices point to each other subsequent order") {
    TestDevice d1 = TestDevice();
    TestDevice d2 = TestDevice();
    TestDevice d3 = TestDevice();
    REQUIRE(Device::next(d1) == &d2);
    REQUIRE(Device::next(d2) == &d3);
    REQUIRE(Device::next(d3) == &d1);
  }

  SECTION("A destroyed device is no longer referenced") {
    TestDevice d1 = TestDevice();
    TestDevice d2 = TestDevice();
    {
      TestDevice d3 = TestDevice();
      REQUIRE(Device::next(d1) == &d2);
      REQUIRE(Device::next(d2) == &d3);
      REQUIRE(Device::next(d3) == &d1);
    }
    REQUIRE(Device::next(d1) == &d2);
    REQUIRE(Device::next(d2) == &d1);
  }

  SECTION("Destroying the last (or: only) item cleans up properly") {
    {
      TestDevice d1 = TestDevice();
    }
    TestDevice d2 = TestDevice();
    REQUIRE(Device::next(d2) == &d2);
  }

}
