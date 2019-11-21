typedef std::string String;
#define String(x) std::to_string(x)

unsigned long millis(void) {
  return Virtuino::millis_;
}

int digitalRead(uint8_t pin) {
    return Virtuino::digitalInputs_[pin];
}

void digitalWrite(uint8_t pin, uint8_t val) {
  Virtuino::digitalOutputs_[pin] = val;
}

uint8_t digitalPinToBitMask(uint8_t pin) {
  return ~pin;
}

uint8_t analogPinToChannel(uint8_t pin) {
  return ~pin;
}

struct SoftwareSerial {
  static const int DEC = 10;

  void begin(long speed);

  size_t print(const String &);
  size_t print(const char[]);
  // size_t print(char);
  // size_t print(unsigned char, int = DEC);
  // size_t print(int, int = DEC);
  // size_t print(unsigned int, int = DEC);
  // size_t print(long, int = DEC);
  size_t print(unsigned long, int = DEC);
  // size_t print(double, int = 2);

  size_t println(const String &s);
  size_t println(const char[]);
  // size_t println(char);
  // size_t println(unsigned char, int = DEC);
  // size_t println(int, int = DEC);
  // size_t println(unsigned int, int = DEC);
  // size_t println(long, int = DEC);
  // size_t println(unsigned long, int = DEC);
  // size_t println(double, int = 2);
  // size_t println(void);
} Serial;

void SoftwareSerial::begin(long speed) {}

size_t SoftwareSerial::print(const String& s) {
  std::cout << s;
  return 0;
}

size_t SoftwareSerial::print(const char* s) {
  std::cout << s;
  return 0;
}

size_t SoftwareSerial::print(unsigned long x, int base) {
  std::cout << x;
  return 0;
}

size_t SoftwareSerial::println(const String& s) {
  std::cout << s << std::endl;
  return 0;
}

size_t SoftwareSerial::println(const char* s) {
  std::cout << s << std::endl;
  return 0;
}
