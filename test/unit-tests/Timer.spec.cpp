#include "../../src/Timer.h"

namespace TimerSpec {
  Timer* t;
}

TEST_CASE("[Timer]") {

  CallSpy spy;
  Virtuino virtuino;

  SECTION("A Timer is AutoUpdated") {
    Timer t;
    AutoUpdated& au = t; // The “assertion” is that this compiles
  }

  SECTION("The handler function should not be invoked without the timer being started") {
    Timer t;
    t.onTrigger(spy.Void);
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled() == false);
  }

  SECTION("If there is no handler function, nothing happens") {
    Timer t;
    t.start(10);
    REQUIRE_NOTHROW(virtuino.elapseMillis(11));
    REQUIRE(t.isActive() == false);
  }

  SECTION("`isActive` should inform about the timer status") {
    Timer t;
    REQUIRE(t.isActive() == false);
    t.start(10);
    REQUIRE(t.isActive() == true);
    virtuino.elapseMillis(11);
    REQUIRE(t.isActive() == false);
  }

  SECTION("The handler function should not be invoked before the time is elapsed") {
    Timer t;
    t.onTrigger(spy.Void);
    t.start(10);
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled() == false);
    virtuino.elapseMillis(3);
    REQUIRE(spy.hasBeenCalled() == false);
    virtuino.elapseMillis(3);
    REQUIRE(spy.hasBeenCalled() == false);
    virtuino.elapseMillis(3);
    REQUIRE(spy.hasBeenCalled() == false);
    virtuino.elapseMillis(1);
    REQUIRE(spy.hasBeenCalled());
  }

  SECTION("The handler should only be invoked once after the time has elapsed") {
    Timer t;
    t.onTrigger(spy.Void);
    t.start(1);
    virtuino.elapseMillis(3);
    REQUIRE(spy.counter() == 1);
  }

  SECTION("The timer can be cancelled") {
    Timer t;
    t.onTrigger(spy.Void);
    t.start(10);
    virtuino.elapseMillis(3);
    t.cancel();
    REQUIRE(t.isActive() == false);
    virtuino.elapseMillis(50);
    REQUIRE(spy.hasBeenCalled() == false);
  }

  SECTION("Calling `start()` or `start(long)` restarts the timer") {
    Timer t;
    t.onTrigger(spy.Void);
    t.start(10);
    virtuino.elapseMillis(9);
    t.start(20);
    virtuino.elapseMillis(19);
    t.start(30);
    virtuino.elapseMillis(29);
    REQUIRE(spy.hasBeenCalled() == false);
    virtuino.elapseMillis(2);
    REQUIRE(spy.hasBeenCalled());
  }

  SECTION("Timer can be restarted from within callback", "[Timer]") {
    // Cannot capture local object in `onTrigger` callback, hence the workaround
    // with a global pointer
    struct TimerSpecRAII {
      TimerSpecRAII() { TimerSpec::t = new Timer(); }
      ~TimerSpecRAII() { delete TimerSpec::t; }
    } tsr;
    TimerSpec::t->onTrigger([](){ TimerSpec::t->start(5); });
    TimerSpec::t->start(5);
    virtuino.elapseMillis(6);
    REQUIRE(TimerSpec::t->isActive());
    virtuino.elapseMillis(6);
    REQUIRE(TimerSpec::t->isActive());
  }
}
