struct Result {
  String name;
  uint8_t actualSize;
  uint8_t expectedSize;

  bool ok() {
    return this->expectedSize == this->actualSize;
  }
};

template<class T>
struct Test: public Result {
  Test(String name)
  {
    this->name = name;
  }

  Test& expectSize(uint8_t s) {
    this->expectedSize = s;
    this->actualSize = sizeof(T);
    return *this;
  }
};

void printout(Result& r) {
  const String _ = "          ";
  Serial.print(r.ok() ? "[OK]      " : "[ERROR]   ");
  Serial.print("# ");
  Serial.print(r.name);
  Serial.print(": ");
  Serial.println();

  Serial.print(_);
  Serial.print("Size: ");
  Serial.print(r.actualSize);
  Serial.print(" bytes (");
  Serial.print(r.expectedSize);
  Serial.print(")");
  Serial.println();

  Serial.println();
}
