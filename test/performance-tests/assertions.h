DigitalInput di(2);
DigitalOutput dt(4);

Test tests[] = {

  Test("DigitalInput")
    .sizeOf<DigitalInput>(4)
    .benchmark("value()", 1.7, [](){ di.value(); })

  ,Test("DigitalOutput")
    .sizeOf<DigitalOutput>(6)
    .benchmark("write()", 2.7, [](){ dt.write(HIGH); })
    .benchmark("toggle()", 3.3, [](){ dt.toggle(); })

  ,Test("Observer")
    .sizeOf<Observer>(14)

  ,Test("Metronome")
    .sizeOf<Metronome>(15)

  ,Test("Timer")
    .sizeOf<Timer>(15)

  ,Test("Loop")
    .sizeOf<Loop>(7)

};
