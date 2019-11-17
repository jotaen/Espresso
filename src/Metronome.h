#ifndef __YPS_METRONOME_H__
#define __YPS_METRONOME_H__

class Metronome: public Device {
  
  typedef void (*Handler)();

public:
  Metronome()
  : handler(0)
  , active(false)
  , intervalMillis(0)
  , nextLoop(0)
  {}

  void onTrigger(Handler h) {
    this->handler = h;
  }

  void runMillis(unsigned long interval) {
    this->intervalMillis = interval;
    this->nextLoop = millis() + interval;
    this->active = true;
    this->invoke();
  }

  void run() {
    runMillis(0);
  }

  void stop() {
    this->active = false;
  }

  bool isActive() {
    return active;
  }

protected:
  void onLoop() {
    if (!this->active || millis() < this->nextLoop) {
      return;
    }
    this->invoke();
    this->nextLoop += this->intervalMillis;
  }

  void invoke() {
    if (this->handler) {
      this->handler();
    }
  }

  Handler handler;
  bool active;
  unsigned long intervalMillis;
  unsigned long nextLoop;
};

#endif
