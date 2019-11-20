DigitalInput di(1);

Result results[] = {

  Test<DigitalInput>("DigitalInput")
    .expectSize(4)
    .benchmark("digitalRead", [](){ di.value(); }),

  Test<DigitalOutput>("DigitalOutput")
    .expectSize(6),

  Test<Observer>("Observer")
    .expectSize(14),

  Test<Metronome>("Metronome")
    .expectSize(15),

  Test<Timer>("Timer")
    .expectSize(15),

  Test<Loop>("Loop")
    .expectSize(7),

};
