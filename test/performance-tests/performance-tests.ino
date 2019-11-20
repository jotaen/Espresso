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
    Serial.print(t.name);
    Serial.println();

    Serial.print(_);
    Serial.print("Size: ");
    Serial.print(t.actualSize);
    Serial.print(" bytes [");
    Serial.print(t.expectedSize);
    Serial.print(" bytes]");
    Serial.println();

    for(uint8_t i=0; i<t.benchmarkCount; i++) {
      Serial.print(_);
      Serial.print("Benchmark: ");
      Serial.print(t.benchmarkName[i]);
      Serial.print(" ");
      Serial.print(r.benchmarkActual[i]);
      Serial.print(" μs [");
      Serial.print(t.benchmarkExpected[i]);
      Serial.print(" μs]");
      Serial.println();
    }

    Serial.println();
  }
  while(true);
}
