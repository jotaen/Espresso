#define CHECK(...) Result* results[] = { __VA_ARGS__ };

struct Result {
  String name;
  uint8_t actual_size;
  uint8_t expected_size;
  bool ok;
};

template<class T>
Result* test(String name, uint8_t expected_size) {
  Result* r = new Result;
  r->name = name;
  r->actual_size = sizeof(T);
  r->expected_size = expected_size;
  r->ok = (r->actual_size == r->expected_size);
  return r;
}

void printout(Result* r) {
  const String _ = "          ";
  Serial.print(r->ok ? "[OK]      " : "[ERROR]   ");
  Serial.print("# ");
  Serial.print(r->name);
  Serial.print(": ");
  Serial.println();

  Serial.print(_);
  Serial.print("Size: ");
  Serial.print(r->actual_size);
  Serial.print(" bytes (");
  Serial.print(r->expected_size);
  Serial.print(")");
  Serial.println();

  Serial.println();
}
