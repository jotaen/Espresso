#include "../lib/catch.hpp"
#include "core.h"
#include "Device.h"

TEST_CASE("[Device]") {

  _core::reset();

  SECTION("A new device is attached") {
    Device d = Device();
    REQUIRE(d.isAttached() == true);
  }

  SECTION("A device can be attached and detached") {
    Device d = Device();
    d.detach();
    REQUIRE(d.isAttached() == false);
    d.attach(true);
    REQUIRE(d.isAttached() == true);
    d.attach(false);
    REQUIRE(d.isAttached() == false);
  }

  SECTION("An detached device doesn’t point anywhere") {
    Device d = Device();
    d.detach();
    REQUIRE(_core::next(d) == NULL);
  }

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
    Device d3 = Device();
    d2.detach();
    REQUIRE(_core::next(d1) == &d3);
    REQUIRE(_core::next(d3) == &d1);
  }

  SECTION("Re-attaching a device doesn’t change the chaining order") {
    Device d1 = Device();
    Device d2 = Device();
    Device d3 = Device();
    d2.attach();
    REQUIRE(_core::next(d1) == &d2);
    REQUIRE(_core::next(d2) == &d3);
    REQUIRE(_core::next(d3) == &d1);
  }

  SECTION("Re-detaching is a no-op") {
    Device d1 = Device();
    Device d2 = Device();
    d1.detach();
    d1.detach();
    REQUIRE(_core::next(d2) == &d2);
  }

  SECTION("Detaching the last (or: only) item cleans up properly") {
    Device d1 = Device();
    d1.detach();
    Device d2 = Device();
    REQUIRE(_core::next(d2) == &d2);
  }

  SECTION("Destroying device objects also detaches them") {
    Device d1 = Device();
    {
      Device d2 = Device();
    }
    REQUIRE(_core::next(d1) == &d1);
  }

}
