#ifndef __ESPRESSO_LOOPBENCHMARK_H__
#define __ESPRESSO_LOOPBENCHMARK_H__

#include "../core/AutoUpdated.h"

class LoopBenchmark: public AutoUpdated {
public:
  LoopBenchmark(unsigned long interval = 1000)
  : interval(interval) 
  , lastMillis(0) 
  , loopCounter(0) {}

protected:
  void onLoop() {
    const unsigned long now = millis();
    this->loopCounter++;

    if (now - this->lastMillis >= this->interval) {
      logger::info("Benchmark: " +
        String(this->loopCounter) +
        " loops/" +
        String(this->interval) +
        "ms"
      );
      this->lastMillis = now;
      this->loopCounter = 0;
    }
  }

  unsigned long interval;
  unsigned long lastMillis;
  unsigned long loopCounter;
};

#endif
