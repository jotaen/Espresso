#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>
#include "lib.h"
#include "assertions.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(Test& t : tests) {
    Result r(t);
    const String _ = "         ";
    Serial.print(r.ok ? "OK       " : "FAILED   ");
    Serial.print("# ");
    Serial.print(r.name);
    Serial.println();

    Serial.print(_);
    Serial.print("Size: ");
    Serial.print(r.actualSize);
    Serial.print(" bytes [");
    Serial.print(r.expectedSize);
    Serial.print(" bytes]");
    Serial.println();

    if (r.hasBenchmark != 0) {
      Serial.print(_);
      Serial.print("Benchmark: ");
      Serial.print(r.benchmarkName);
      Serial.print(" ");
      Serial.print(r.benchmarkActual);
      Serial.print(" μs [");
      Serial.print(r.benchmarkExpected);
      Serial.print(" μs]");
      Serial.println();
    }

    Serial.println();
  }
  while(true);
}
