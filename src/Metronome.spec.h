#include <catch.hpp>
#include <World.h>
#include <utils.h>
#include "Metronome.h"

TEST_CASE("[Metronome]") {

  callspy::reset();
  World::reset();

  SECTION("A Metronome is a Device") {
    Metronome m = Metronome(noop);
    Device& d = m; // The “assertion” is that this compiles
  }

  SECTION("The handler function invocation should begin immediately") {
    Metronome m = Metronome(callspy::Void);
    m.runMillis(5);
    REQUIRE(callspy::reporter.hasBeenCalled);
  }

  SECTION("`isActive`: Should inform about whether the timer is active or idling") {
    Metronome m = Metronome(noop);
    REQUIRE(m.isActive() == false);
    m.runMillis(10);
    REQUIRE(m.isActive());
    m.stop();
    REQUIRE(m.isActive() == false);
    World::elapseMillis(50);
    REQUIRE(m.isActive() == false);
  }

  SECTION("`runMillis`: The handler function should be invoked after time has elapsed") {
    const unsigned long interval = 50;
    Metronome m = Metronome(callspy::Void);
    m.runMillis(interval);
    World::elapseMillis(interval);
    REQUIRE(callspy::reporter.hasBeenCalled);
    REQUIRE(callspy::reporter.count == 2);
  }

  SECTION("`runMillis`: The handler function should be invoked recurringly") {
    const unsigned long interval = 50;
    Metronome m = Metronome(callspy::Void);
    m.runMillis(interval);
    World::elapseMillis(3*interval);
    REQUIRE(callspy::reporter.hasBeenCalled);
    REQUIRE(callspy::reporter.count == 4);
  }

  SECTION("`runMillis`: The handler should not be invoked anymore after the metronome was stopped") {
    const unsigned long interval = 50;
    Metronome m = Metronome(callspy::Void);
    m.runMillis(interval);
    World::elapseMillis(3*interval);
    m.stop();
    World::elapseMillis(3*interval);
    REQUIRE(callspy::reporter.count == 4);
  }

}
