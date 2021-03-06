typedef void (*Case)();
const double m = 1.03; // 3% margin for performance benchmarks

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

  Test& benchmark(String name, double expectedRuntimeMicros, Case c) {
    this->benchmarkName[this->benchmarkCount] = name;
    this->benchmarkExpected[this->benchmarkCount] = expectedRuntimeMicros;
    this->benchmarkCase[this->benchmarkCount] = c;
    this->benchmarkCount++;
    return *this;
  }

  String name = "";
  uint8_t actualSize = 0;
  uint8_t expectedSize = 0;
  double benchmarkExpected[8] = {0};
  String benchmarkName[8] = {""};
  Case benchmarkCase[8] = {0};
  uint8_t benchmarkCount = 0;

protected:
  Test() {}
};

class Result {
public:
  Result(const Test& t)
  : t(t) {
    for(uint8_t i=0; i<t.benchmarkCount; i++) {
      this->benchmarkActual[i] = this->benchmark(t.benchmarkCase[i]);
    }
    this->ok = this->overall();
  }

  double benchmarkActual[8] = {999999};
  bool ok = false;

private:
  const Test t;

  double benchmark(const Case& benchmarkCase) {
    const unsigned int iterations = 65535;
    const unsigned long start = micros();
    for (unsigned int i=iterations; i!=0; --i) {
      benchmarkCase();
    }
    const unsigned long stop = micros();
    const unsigned long runtime = stop - start;
    return ((double)runtime) / iterations;
  }

  bool overall() {
    bool size = (this->t.actualSize == this->t.expectedSize);
    bool benchmark = true;
    for(uint8_t i=0; benchmark && i<this->t.benchmarkCount; i++) {
      benchmark = (this->benchmarkActual[i] <= this->t.benchmarkExpected[i]);
    }
    return size && benchmark;
  }
};

void run(const Test& t) {
  Serial.begin(9600);
  Result r(t);
  String ___ = "            ";

  Serial.print("# ");
  Serial.println(t.name);
  Serial.println();

  Serial.print("Size:       ");
  Serial.print(t.actualSize);
  Serial.print(" bytes [");
  Serial.print(t.expectedSize);
  Serial.print(" bytes]");
  Serial.println();
  Serial.println();

  Serial.print("Benchmark:  ");
  for(uint8_t i=0; i<t.benchmarkCount; i++) {
    Serial.print(t.benchmarkName[i]);
    Serial.print(" ");
    Serial.print(r.benchmarkActual[i]);
    Serial.print(" μs [");
    Serial.print(t.benchmarkExpected[i]);
    Serial.print(" μs]");
    Serial.println();
    Serial.print(___);
  }

  Serial.println();
  Serial.println();
  Serial.print("=> ");
  Serial.println(r.ok ? "OK" : "FAILED");
  while(true);
}
