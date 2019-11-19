#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "Metronome.h"
#include "util/callspy.h"

TEST_CASE("[Metronome]") {

  callspy::reset();
  Virtuino::clear();

  SECTION("A Metronome is AutoUpdated") {
    Metronome m;
    AutoUpdated& au = m; // The “assertion” is that this compiles
  }

  SECTION("The handler function invocation should begin immediately") {
    Metronome m;
    m.onTrigger(callspy::Void);
    m.runMillis(5);
    REQUIRE(callspy::hasBeenCalled());
  }

  SECTION("If no handler function is given, nothing happens") {
    Metronome m;
    REQUIRE_NOTHROW(m.run());
  }

  SECTION("`isActive`: Should inform about whether the timer is active or idling") {
    Metronome m;
    REQUIRE(m.isActive() == false);
    m.runMillis(10);
    REQUIRE(m.isActive());
    m.stop();
    REQUIRE(m.isActive() == false);
    Virtuino::elapseMillis(50);
    REQUIRE(m.isActive() == false);
  }

  SECTION("`runMillis`: The handler function should be invoked after time has elapsed") {
    const unsigned long interval = 50;
    Metronome m;
    m.onTrigger(callspy::Void);
    m.runMillis(interval);
    Virtuino::elapseMillis(interval);
    REQUIRE(callspy::hasBeenCalled());
    REQUIRE(callspy::counter() == 2);
  }

  SECTION("`runMillis`: The handler function should be invoked recurringly") {
    const unsigned long interval = 50;
    Metronome m;
    m.onTrigger(callspy::Void);
    m.runMillis(interval);
    Virtuino::elapseMillis(3*interval);
    REQUIRE(callspy::hasBeenCalled());
    REQUIRE(callspy::counter() == 4);
  }

  SECTION("`runMillis`: The handler should not be invoked anymore after the metronome was stopped") {
    const unsigned long interval = 50;
    Metronome m;
    m.onTrigger(callspy::Void);
    m.runMillis(interval);
    Virtuino::elapseMillis(3*interval);
    m.stop();
    Virtuino::elapseMillis(3*interval);
    REQUIRE(callspy::counter() == 4);
  }

  SECTION("`run`: The handler should be invoked straight away and as often as possible") {
    Metronome m;
    m.onTrigger(callspy::Void);
    m.run();
    REQUIRE(callspy::hasBeenCalled());
    REQUIRE(callspy::counter() == 1);
    Virtuino::elapseMillis(10);
    REQUIRE(callspy::counter() > 2); // in reality, we cannot tell exactly!
  }

}
