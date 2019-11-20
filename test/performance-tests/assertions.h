DigitalInput digitalInput(2);
DigitalOutput digitalOutput(4);

bool observerState = false;
Observer observer([](){ return observerState; });

Metronome metronome;

Timer timer;

Loop looper;

void setup() {
  observerState = true; // change to trigger observer initially
  observer.onTrue([](){ observerState = !observerState; });
  observer.onFalse([](){ observerState = !observerState; });

  metronome.onTrigger([](){});
  metronome.run(0);

  timer.onTrigger([](){ timer.start(0); });
  timer.start(0);

  looper.onTrigger([](){});
}

const double m = 1.03; // 3% margin for performance benchmarks
Test tests[] = {

  Test("DigitalInput")
    .sizeOf<DigitalInput>(4)
    .benchmark("value()", 1.45*m, [](){ digitalInput.value(); })

  ,Test("DigitalOutput")
    .sizeOf<DigitalOutput>(6)
    .benchmark("write()", 2.46*m, [](){ digitalOutput.write(HIGH); })
    .benchmark("toggle()", 3.11*m, [](){ digitalOutput.toggle(); })

  ,Test("Observer")
    .sizeOf<Observer>(14)
    .benchmark("update()", 5.63*m, [](){ observer.update(); })

  ,Test("Metronome")
    .sizeOf<Metronome>(15)
    .benchmark("update()", 7.68*m, [](){ metronome.update(); })

  ,Test("Timer")
    .sizeOf<Timer>(15)
    .benchmark("update()", 2.77*m, [](){ timer.update(); })

  ,Test("Loop")
    .sizeOf<Loop>(7)
    .benchmark("update()", 2.52*m, [](){ looper.update(); })

};
