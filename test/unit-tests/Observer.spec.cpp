#include "../../src/Observer.h"

bool providerValue = false;

TEST_CASE("[Observer]") {

  Virtuino virtuino(Virtuino::DESTROY);
  CallSpy spy;
  providerValue = false;

  SECTION("An Observer is AutoUpdated") {
    Observer<bool> o;
    AutoUpdated& au = o; // The “assertion” is that this compiles
  }

  SECTION("Absence of handlers is dealt with gracefully") {
    Observer<bool> o;
    o.observe([](){ return providerValue; });
    REQUIRE_NOTHROW(virtuino.flush());
    providerValue = true;
    REQUIRE_NOTHROW(virtuino.flush());
  }

  SECTION("Absence of provider is dealt with gracefully") {
    Observer<bool> o;
    o.onChange([](bool){});
    REQUIRE_NOTHROW(virtuino.flush());
  }

  SECTION("A provider can be optionally specified upon construction") {
    Observer<bool> o([](){ return providerValue; });
    o.onChange(spy.Bool);
    REQUIRE(spy.hasBeenCalled() == false);
    providerValue = true;
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled());
  }

  SECTION("Change handler gets called once when observed value changes") {
    Observer<bool> o([](){ return providerValue; });
    o.onChange(spy.Bool);
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled() == false); // since there was no change so far
    providerValue = true;
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled() == true);
  }

  SECTION("Change handler gets invoked with the current value") {
    Observer<bool> o([](){ return providerValue; });
    o.onChange([](bool val){ if (val != providerValue) throw "Wrong argument"; });
    providerValue = true;
    REQUIRE_NOTHROW(virtuino.flush());
  }

  SECTION("Change handler gets called once upon change") {
    Observer<bool> o([](){ return providerValue; });
    o.onChange(spy.Bool);
    virtuino.elapseMillis(10);
    providerValue = true;
    virtuino.elapseMillis(100);
    REQUIRE(spy.counter() == 1);
    REQUIRE(spy.hasBeenCalled() == true);
  }

  SECTION("Observer can be enabled and disabled") {
    Observer<bool> o([](){ return providerValue; });
    o.onChange(spy.Bool);
    o.disable();
    virtuino.flush();
    REQUIRE(o.isActive() == false);
    REQUIRE(spy.hasBeenCalled() == false);
    providerValue = true;
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled() == false);

    o.enable();
    virtuino.flush();
    REQUIRE(o.isActive() == true);
    REQUIRE(spy.hasBeenCalled());
  }

}
