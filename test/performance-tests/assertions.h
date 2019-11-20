DigitalInput di(2);
DigitalOutput dt(4);

bool observerState = false;
Observer o([](){ return observerState; });

void setup() {
  observerState = true; // change to trigger observer initially
  o.onTrue([](){ observerState = !observerState; });
  o.onFalse([](){ observerState = !observerState; });
}

const double m = 1.03; // 3% margin for performance benchmarks
Test tests[] = {

  Test("DigitalInput")
    .sizeOf<DigitalInput>(4)
    .benchmark("value()", 1.45*m, [](){ di.value(); })

  ,Test("DigitalOutput")
    .sizeOf<DigitalOutput>(6)
    .benchmark("write()", 2.46*m, [](){ dt.write(HIGH); })
    .benchmark("toggle()", 3.11*m, [](){ dt.toggle(); })

  ,Test("Observer")
    .sizeOf<Observer>(14)
    .benchmark("update()", 5.38*m, [](){ o.update(); })

  ,Test("Metronome")
    .sizeOf<Metronome>(15)

  ,Test("Timer")
    .sizeOf<Timer>(15)

  ,Test("Loop")
    .sizeOf<Loop>(7)

};
