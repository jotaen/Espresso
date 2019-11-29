class Virtuino {
public:
  enum InitMode { RESET, DESTROY };

  Virtuino(InitMode im) {
    millis_ = 0;
    digitalInputs_.clear();
    digitalOutputs_.clear();
    analogInputs_.clear();
    analogOutputs_.clear();
    adcValue_ = 0;
    setup();
    if (im == DESTROY) {
      pinModes_.clear();
    }
  }

  void flush(unsigned short times = 2) {
    for(unsigned short i=0; i<times; i++) {
      loop();
    }
  }

  void elapseMillis(unsigned long m) {
    const unsigned int target = millis_ + m;
    while(millis_ < target) {
      millis_ += 1;
      flush();
    }
  }

  void freezeMillis(unsigned long m) {
    millis_ += m;
    flush();
  }

  uint8_t checkPinMode(uint8_t pin) {
    return pinModes_.at(pin); // throws if key not set
  }

  void setDigitalInput(uint8_t pin, int val) {
    if (checkPinMode(pin) != INPUT) {
      throw std::invalid_argument("`pin`");
    }
    digitalInputs_[pin] = val;
    flush();
  }

  int checkDigitalOutput(uint8_t pin) {
    if (checkPinMode(pin) != OUTPUT) {
      throw std::invalid_argument("`pin`");
    }
    return digitalOutputs_.at(pin); // throws if key not set
  }

  void setAnalogInput(uint8_t pin, int val) {
    analogInputs_[pin] = val;
    flush(10); // TODO workaround to make sure that “slow” ADC has run on that pin
  }

  int checkAnalogOutput(uint8_t pin) {
    return analogOutputs_.at(pin); // throws if key not set
  }

private:
  friend unsigned long millis(void);
  friend int digitalRead(uint8_t);
  friend void digitalWrite(uint8_t, uint8_t);
  friend class rdn;

  static unsigned long millis_;
  static std::map<uint8_t, uint8_t> pinModes_;
  static std::map<uint8_t, int> digitalInputs_;
  static std::map<uint8_t, int> digitalOutputs_;
  static std::map<uint8_t, int> analogInputs_;
  static std::map<uint8_t, int> analogOutputs_;
  static int adcValue_;
};

unsigned long Virtuino::millis_ = 0;
std::map<uint8_t, uint8_t> Virtuino::pinModes_;
std::map<uint8_t, int> Virtuino::digitalInputs_;
std::map<uint8_t, int> Virtuino::digitalOutputs_;
std::map<uint8_t, int> Virtuino::analogInputs_;
std::map<uint8_t, int> Virtuino::analogOutputs_;
int Virtuino::adcValue_ = 0;
