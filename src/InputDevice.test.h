#include "../lib/catch.hpp"
#include "InputDevice.h"

TEST_CASE("[InputDevice]") {

  InputDevice::YPS_ROOT_INPUTDEVICE = NULL;

  SECTION("A new device is attached") {
    InputDevice d = InputDevice();
    REQUIRE(d.isAttached() == true);
  }

  SECTION("A device can be attached and detached") {
    InputDevice d = InputDevice();
    d.detach();
    REQUIRE(d.isAttached() == false);
    d.attach(true);
    REQUIRE(d.isAttached() == true);
    d.attach(false);
    REQUIRE(d.isAttached() == false);
  }

  SECTION("An detached device doesn’t point anywhere") {
    InputDevice d = InputDevice();
    d.detach();
    REQUIRE(d.next() == NULL);
  }

  SECTION("A single active device points to itself") {
    InputDevice d = InputDevice();
    REQUIRE(d.next() == &d);
  }

  SECTION("Attached devices point to each other subsequent order") {
    InputDevice d1 = InputDevice();
    InputDevice d2 = InputDevice();
    InputDevice d3 = InputDevice();
    REQUIRE(d1.next() == &d2);
    REQUIRE(d2.next() == &d3);
    REQUIRE(d3.next() == &d1);
  }

  SECTION("A detached device is no longer referenced") {
    InputDevice d1 = InputDevice();
    InputDevice d2 = InputDevice();
    InputDevice d3 = InputDevice();
    d2.detach();
    REQUIRE(d1.next() == &d3);
    REQUIRE(d3.next() == &d1);
  }

  SECTION("Re-attaching a device doesn’t change the chaining order") {
    InputDevice d1 = InputDevice();
    InputDevice d2 = InputDevice();
    InputDevice d3 = InputDevice();
    d2.attach();
    REQUIRE(d1.next() == &d2);
    REQUIRE(d2.next() == &d3);
    REQUIRE(d3.next() == &d1);
  }

  SECTION("Re-detaching is a no-op") {
    InputDevice d1 = InputDevice();
    InputDevice d2 = InputDevice();
    d1.detach();
    d1.detach();
    REQUIRE(d2.next() == &d2);
  }

  SECTION("Detaching the last (or: only) item cleans up properly") {
    InputDevice d1 = InputDevice();
    d1.detach();
    InputDevice d2 = InputDevice();
    REQUIRE(d2.next() == &d2);
  }

}
