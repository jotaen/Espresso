DigitalInput di(2);
DigitalOutput dt(4);

void setup() {
}
Test tests[] = {

  Test("DigitalInput")
    .sizeOf<DigitalInput>(4)
    .benchmark("value()", 1.55, [](){ di.value(); })

  ,Test("DigitalOutput")
    .sizeOf<DigitalOutput>(6)
    .benchmark("write()", 2.55, [](){ dt.write(HIGH); })
    .benchmark("toggle()", 3.20, [](){ dt.toggle(); })

  ,Test("Observer")
    .sizeOf<Observer>(14)

  ,Test("Metronome")
    .sizeOf<Metronome>(15)

  ,Test("Timer")
    .sizeOf<Timer>(15)

  ,Test("Loop")
    .sizeOf<Loop>(7)

};
