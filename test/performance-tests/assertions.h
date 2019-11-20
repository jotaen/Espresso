DigitalInput di(2);
DigitalOutput dt(4);

void setup() {
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

  ,Test("Metronome")
    .sizeOf<Metronome>(15)

  ,Test("Timer")
    .sizeOf<Timer>(15)

  ,Test("Loop")
    .sizeOf<Loop>(7)

};
