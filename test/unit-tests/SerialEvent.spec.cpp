#include "../../src/SerialEvent.h"

namespace SerialEventSpec {
  String byte;
}

TEST_CASE("[SerialEvent]") {

  CallSpy spy;
  Virtuino virtuino(Virtuino::DESTROY);
  SerialEventSpec::byte = "";

  SECTION("SerialEvent is AutoUpdated") {
    SerialEvent se;
    AutoUpdated& au = se; // The “assertion” is that this compiles
  }

  SECTION("Handler doesn’t get called when no data arrived") {
    SerialEvent se;
    se.onEvent(spy.Void);
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled() == false);
  }

  SECTION("Absent handler doesn’t crash") {
    SerialEvent se;
    std::deque<int> q = {1, 2, 3};
    virtuino.populateSerialData(0, q);
    REQUIRE_NOTHROW(virtuino.flush());
  }

  SECTION("Handler gets called when new data arrived") {
    SerialEvent se;
    se.onEvent([](){ SerialEventSpec::byte += String(Serial.read()); });
    std::deque<int> q = {1, 2, 3};
    virtuino.populateSerialData(0, q);
    virtuino.elapseMillis(10);
    REQUIRE(SerialEventSpec::byte == "123");
  }

}
