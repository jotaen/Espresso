#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "Metronome.h"
#include "util/CallSpy.h"

TEST_CASE("[Metronome]") {

  CallSpy spy;
  Virtuino::clear();

  SECTION("A Metronome is AutoUpdated") {
    Metronome m;
    AutoUpdated& au = m; // The “assertion” is that this compiles
  }

  SECTION("The handler function invocation should begin immediately") {
    Metronome m;
    m.onTrigger(spy.Void);
    m.run(5);
    REQUIRE(spy.hasBeenCalled());
  }

  SECTION("If no handler function is given, nothing happens") {
    Metronome m;
    REQUIRE_NOTHROW(m.run(123));
  }

  SECTION("`isActive`: Should inform about whether the timer is active or idling") {
    Metronome m;
    REQUIRE(m.isActive() == false);
    m.run(10);
    REQUIRE(m.isActive());
    m.stop();
    REQUIRE(m.isActive() == false);
    Virtuino::elapseMillis(50);
    REQUIRE(m.isActive() == false);
  }

  SECTION("`run`: The handler function should be invoked after time has elapsed") {
    const unsigned long interval = 50;
    Metronome m;
    m.onTrigger(spy.Void);
    m.run(interval);
    Virtuino::elapseMillis(interval);
    REQUIRE(spy.hasBeenCalled());
    REQUIRE(spy.counter() == 2);
  }

  SECTION("`run`: The handler function should be invoked recurringly") {
    const unsigned long interval = 50;
    Metronome m;
    m.onTrigger(spy.Void);
    m.run(interval);
    Virtuino::elapseMillis(3*interval);
    REQUIRE(spy.hasBeenCalled());
    REQUIRE(spy.counter() == 4);
  }

  SECTION("`run`: The handler should not be invoked anymore after the metronome was stopped") {
    const unsigned long interval = 50;
    Metronome m;
    m.onTrigger(spy.Void);
    m.run(interval);
    Virtuino::elapseMillis(3*interval);
    m.stop();
    Virtuino::elapseMillis(3*interval);
    REQUIRE(spy.counter() == 4);
  }

}
