namespace rdn {
  volatile uint8_t* setupDigitalInputPin(uint8_t, uint8_t, uint8_t);
  volatile uint8_t* setupDigitalOutputPin(uint8_t, uint8_t, uint8_t);
  void digitalWriteUnchecked(uint8_t, volatile uint8_t*, uint8_t);
  int digitalReadUnchecked(uint8_t, volatile uint8_t*);
  void analogReadInit(uint8_t);
  int analogReadTryObtain();
}

class Virtuino {
public:
  Virtuino() {
    millis_ = 0;
    digitalOutputs_.clear();
    digitalInputs_.clear();
    setup();
  }

  void flush() {
    loop();
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
    return digitalOutputs_[pin];
  }

  void setAnalogInput(uint8_t pin, int val) {
    analogInputs_[pin] = val;
    flush();
  }

private:
  friend unsigned long millis(void);
  friend int digitalRead(uint8_t);
  friend void digitalWrite(uint8_t, uint8_t);
  friend volatile uint8_t* rdn::setupDigitalInputPin(uint8_t, uint8_t, uint8_t);
  friend volatile uint8_t* rdn::setupDigitalOutputPin(uint8_t, uint8_t, uint8_t);
  friend void rdn::digitalWriteUnchecked(uint8_t, volatile uint8_t*, uint8_t);
  friend int rdn::digitalReadUnchecked(uint8_t, volatile uint8_t*);
  friend void rdn::analogReadInit(uint8_t);
  friend int rdn::analogReadTryObtain();

  static unsigned long millis_;
  static std::map<uint8_t, uint8_t> pinModes_;
  static std::map<uint8_t, int> digitalInputs_;
  static std::map<uint8_t, int> digitalOutputs_;
  static std::map<uint8_t, int> analogInputs_;
  static unsigned long adcFinished_;
  static int adcValue_;
};

unsigned long Virtuino::millis_ = 0;
std::map<uint8_t, uint8_t> Virtuino::pinModes_;
std::map<uint8_t, int> Virtuino::digitalInputs_;
std::map<uint8_t, int> Virtuino::digitalOutputs_;
std::map<uint8_t, int> Virtuino::analogInputs_;
unsigned long Virtuino::adcFinished_ = 0;
int Virtuino::adcValue_ = -1;
