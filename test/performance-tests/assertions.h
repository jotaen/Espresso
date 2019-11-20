DigitalInput digitalInput(2);
DigitalOutput digitalOutput(4);

bool observerState = false;
Observer observer([](){ return observerState; });

Metronome metronome;

void setup() {
  observerState = true; // change to trigger observer initially
  observer.onTrue([](){ observerState = !observerState; });
  observer.onFalse([](){ observerState = !observerState; });

  metronome.onTrigger([](){});
  metronome.run(0);
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
    .benchmark("update()", 6.61*m, [](){ metronome.update(); })

  ,Test("Timer")
    .sizeOf<Timer>(15)

  ,Test("Loop")
    .sizeOf<Loop>(7)

};
