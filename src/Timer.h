#ifndef __YPS_TIMER_H__
#define __YPS_TIMER_H__

class Timer: public Device {
  
  typedef void (*Handler)();

public:
  Timer(Handler h)
  : handler(h)
  , active(false)
  , trigger(0)
  {}

  void start(unsigned long delayMillis) {
    this->trigger = millis() + delayMillis;
    this->active = true;
  }

  void cancel() {
    this->active = false;
  }

  bool isActive() {
    return this->active;
  }

protected:
  void onLoop() {
    if (!this->active || millis() < this->trigger) {
      return;
    }
    this->handler();
    this->active = false;
  }

  Handler handler;
  bool active;
  unsigned long trigger;
};

#endif
