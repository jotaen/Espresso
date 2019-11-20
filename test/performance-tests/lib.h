typedef void (*Case)();

struct Test {
  Test(String name)
  {
    this->name = name;
  }

  template<class T>
  Test& sizeOf(uint8_t s) {
    this->expectedSize = s;
    this->actualSize = sizeof(T);
    return *this;
  }

  Test& benchmark(String name, unsigned long expectedRuntimeMicros, Case c) {
    this->benchmarkName = name;
    this->benchmarkExpected = expectedRuntimeMicros;
    this->benchmarkCase = c;
    return *this;
  }

  String name = "";
  uint8_t actualSize = 0-1; // max
  uint8_t expectedSize = 0;
  unsigned long benchmarkExpected = 0-1; // max
  String benchmarkName = "";
  Case benchmarkCase = 0;

protected:
  Test() {}
};

class Result: public Test {
public:
  Result(const Test& t) {
    this->name = t.name;
    this->actualSize = t.actualSize;
    this->expectedSize = t.expectedSize;
    this->benchmarkName = t.benchmarkName;
    this->benchmarkExpected = t.benchmarkExpected;
    this->benchmarkCase = t.benchmarkCase;
    this->hasBenchmark = (t.benchmarkCase != 0);
    if (this->hasBenchmark) {
      this->benchmarkActual = this->benchmark();
    }
    this->ok = this->overall();
  }

  double benchmarkActual = 999999;
  bool hasBenchmark = false;
  bool ok = false;

private:
  double benchmark() {
    const unsigned long start = micros();
    const unsigned long iterations = 100000;
    for (unsigned long i=iterations; i!=0; --i) {
      this->benchmarkCase();
    }
    const unsigned long stop = micros();
    const unsigned long runtime = stop - start;
    return ((double)runtime) / iterations;
  }

  bool overall() {
    bool size = (this->actualSize == this->expectedSize);
    bool benchmark = this->hasBenchmark ?
      (this->benchmarkActual < this->benchmarkExpected) : true;
    return size && benchmark;
  }
};
