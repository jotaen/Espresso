#include "../../src/Timer.h"

namespace TimerSpec {
  Timer* t;
}

TEST_CASE("[Timer]") {

  CallSpy spy;
  Virtuino virtuino(Virtuino::DESTROY);

  SECTION("A Timer is AutoUpdated") {
    Timer t;
    AutoUpdated& au = t; // The “assertion” is that this compiles
  }

  SECTION("The handler function invocation should begin immediately") {
    Timer t;
    t.onTrigger(spy.Void);
    t.run(5);
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled());
  }

  SECTION("If no handler function is given, nothing happens") {
    Timer t;
    REQUIRE_NOTHROW(t.run(123));
  }

  SECTION("`isActive`: Should inform about whether the timer is active or idling") {
    Timer t;
    REQUIRE(t.isActive() == false);
    t.run(10);
    REQUIRE(t.isActive());
    t.stop();
    REQUIRE(t.isActive() == false);
    virtuino.elapseMillis(50);
    REQUIRE(t.isActive() == false);
  }

  SECTION("`run`: The handler function should be invoked in the specified interval") {
    const unsigned long interval = 50;
    Timer t;
    t.onTrigger(spy.Void);
    t.run(interval);
    virtuino.flush();
    REQUIRE(spy.counter() == 1);
    virtuino.elapseMillis(interval);
    REQUIRE(spy.counter() == 2);
    virtuino.elapseMillis(interval);
    REQUIRE(spy.counter() == 3);
  }

  SECTION("`run`: The handler function should be invoked recurringly") {
    const unsigned long interval = 50;
    Timer t;
    t.onTrigger(spy.Void);
    t.run(interval);
    virtuino.elapseMillis(20*interval);
    REQUIRE(spy.hasBeenCalled());
    REQUIRE(spy.counter() == 21);
  }

  SECTION("`run`: The first, immediate triggering can be postponed till the next trigger") {
    const unsigned long interval = 50;
    Timer t;
    t.onTrigger(spy.Void);
    t.run(interval, Timer::START_DELAYED);
    REQUIRE(spy.hasBeenCalled() == false);
    virtuino.elapseMillis(interval);
    REQUIRE(spy.counter() == 1);
  }

  SECTION("`run`: The handler should not be invoked anymore after the Timer was stopped") {
    const unsigned long interval = 50;
    Timer t;
    t.onTrigger(spy.Void);
    t.run(interval);
    virtuino.elapseMillis(3*interval);
    t.stop();
    REQUIRE(spy.counter() == 4);
    virtuino.elapseMillis(3*interval);
    REQUIRE(spy.counter() == 4);
  }

  SECTION("`runOnce`: The handler should be invoked once after the time has elapsed") {
    Timer t;
    t.onTrigger(spy.Void);
    t.runOnce(10);
    virtuino.elapseMillis(3);
    REQUIRE(spy.hasBeenCalled() == false);
    virtuino.elapseMillis(3);
    REQUIRE(spy.hasBeenCalled() == false);
    virtuino.elapseMillis(3);
    REQUIRE(spy.hasBeenCalled() == false);
    virtuino.elapseMillis(1);
    REQUIRE(spy.hasBeenCalled());
  }

  SECTION("`runOnce`: The handler should only be invoked once") {
    Timer t;
    t.onTrigger(spy.Void);
    t.runOnce(10);
    virtuino.elapseMillis(50);
    REQUIRE(spy.counter() == 1);
  }

  SECTION("`runOnce`: It can be cancelled") {
    Timer t;
    t.onTrigger(spy.Void);
    t.runOnce(10);
    virtuino.elapseMillis(3);
    t.stop();
    REQUIRE(t.isActive() == false);
    virtuino.elapseMillis(50);
    REQUIRE(spy.hasBeenCalled() == false);
  }

  SECTION("`runOnce`: Calling `runOnce` again restarts the timer from that point in time") {
    Timer t;
    t.onTrigger(spy.Void);
    t.runOnce(10);
    virtuino.elapseMillis(9);
    t.runOnce(20);
    virtuino.elapseMillis(19);
    t.runOnce(30);
    virtuino.elapseMillis(29);
    REQUIRE(spy.hasBeenCalled() == false);
    virtuino.elapseMillis(2);
    REQUIRE(spy.hasBeenCalled());
  }

  SECTION("`once`: It can be restarted from within callback") {
    // Cannot capture local object in `onTrigger` callback, hence the workaround
    // with a global pointer
    struct TimerSpecRAII {
      TimerSpecRAII() { TimerSpec::t = new Timer(); }
      ~TimerSpecRAII() { delete TimerSpec::t; }
    } msr;
    TimerSpec::t->onTrigger([](){ TimerSpec::t->runOnce(5); });
    TimerSpec::t->runOnce(5);
    virtuino.elapseMillis(6);
    REQUIRE(TimerSpec::t->isActive());
    virtuino.elapseMillis(6);
    REQUIRE(TimerSpec::t->isActive());
  }

  SECTION("`interval` returns current interval") {
    Timer t;
    REQUIRE(t.interval() == 0);
    t.run(10);
    REQUIRE(t.interval() == 10);
    t.runOnce(20);
    REQUIRE(t.interval() == 20);
  }

  SECTION("`interval` adjusts the interval on a running timer after the fact") {
    Timer t;
    t.onTrigger(spy.Void);
    t.runOnce(100);
    virtuino.elapseMillis(90);
    t.interval(200);
    virtuino.elapseMillis(100);
    t.interval(500);
    virtuino.elapseMillis(300);
    REQUIRE(spy.hasBeenCalled() == false);
    t.interval(1);
    virtuino.flush();
    REQUIRE(spy.hasBeenCalled());
  }

}
