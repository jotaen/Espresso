DigitalInput di(2);
DigitalOutput dt(4);

Test tests[] = {

  Test("DigitalInput")
    .sizeOf<DigitalInput>(4)
    .benchmark("value()", 2, [](){ di.value(); })

  ,Test("DigitalOutput")
    .sizeOf<DigitalOutput>(6)
    .benchmark("write()", 3, [](){ dt.write(HIGH); })
    .benchmark("toggle()", 4, [](){ dt.toggle(); })

  ,Test("Observer")
    .sizeOf<Observer>(14)

  ,Test("Metronome")
    .sizeOf<Metronome>(15)

  ,Test("Timer")
    .sizeOf<Timer>(15)

  ,Test("Loop")
    .sizeOf<Loop>(7)

};
