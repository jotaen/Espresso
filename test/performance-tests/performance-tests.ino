#define ESPRESSO_INCLUDES_ONLY
#include <Espresso.h>

class Result {
public:
  typedef void (*Case)();

  String name() { return this->name_; }
  uint8_t actualSize() { return this->actualSize_; }
  uint8_t expectedSize() { return this->expectedSize_; }

  double benchmark() {
    if (this->benchmarkCase_ == 0) {
      return 0;
    }
    const unsigned long start = micros();
    for (unsigned long i=100000; i!=0; --i) {
      this->benchmarkCase_();
    }
    const unsigned long stop = micros();
    const unsigned long runtime = stop - start;
    return runtime * 0.00001;
  }

  bool ok() {
    return (this->expectedSize_ == this->actualSize_);
  }

protected:
  String name_ = "";

  uint8_t actualSize_ = 0;
  uint8_t expectedSize_ = 0;

  String benchmarkDescription_ = "";
  Case benchmarkCase_ = 0;
};

template<class T>
struct Test: public Result {
  Test(String name)
  {
    this->name_ = name;
  }

  Test& expectSize(uint8_t s) {
    this->expectedSize_ = s;
    this->actualSize_ = sizeof(T);
    return *this;
  }

  Test& benchmark(String description, Case c) {
    this->benchmarkDescription_ = description;
    this->benchmarkCase_ = c;
    return *this;
  }
};

#include "assertions.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(auto & r : results) {
    const String _ = "          ";
    Serial.print(r.ok() ? "[OK]      " : "[ERROR]   ");
    Serial.print("# ");
    Serial.print(r.name());
    Serial.print(": ");
    Serial.println();

    Serial.print(_);
    Serial.print("Size: ");
    Serial.print(r.actualSize());
    Serial.print(" bytes (");
    Serial.print(r.expectedSize());
    Serial.print(")");
    Serial.println();

    Serial.print(_);
    Serial.print("Benchmark: ");
    Serial.print(r.benchmark());
    Serial.print(" μs");
    Serial.println();

    Serial.println();
  }
  while(true);
}
