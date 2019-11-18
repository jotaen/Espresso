#include <catch.hpp>
#include <Virtuino.h>
#include "Device.h"

class TestDevice: public Device {
public:
  Device* next() {
    return this->nextDevice;
  }
protected:
  void onLoop() {}
};

TEST_CASE("[Device]") {

  Virtuino::clear();

  SECTION("A single active device points to itself") {
    TestDevice d = TestDevice();
    REQUIRE(d.next() == &d);
  }

  SECTION("Devices point to each other subsequent order") {
    TestDevice d1 = TestDevice();
    TestDevice d2 = TestDevice();
    TestDevice d3 = TestDevice();
    REQUIRE(d1.next() == &d2);
    REQUIRE(d2.next() == &d3);
    REQUIRE(d3.next() == &d1);
  }

  SECTION("A destroyed device is no longer referenced") {
    TestDevice d1 = TestDevice();
    TestDevice d2 = TestDevice();
    {
      TestDevice d3 = TestDevice();
      REQUIRE(d1.next() == &d2);
      REQUIRE(d2.next() == &d3);
      REQUIRE(d3.next() == &d1);
    }
    REQUIRE(d1.next() == &d2);
    REQUIRE(d2.next() == &d1);
  }

  SECTION("Destroying the last (or: only) item cleans up properly") {
    {
      TestDevice d1 = TestDevice();
    }
    TestDevice d2 = TestDevice();
    REQUIRE(d2.next() == &d2);
  }

}
