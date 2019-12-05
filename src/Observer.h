#ifndef __ESPRESSO_OBSERVER_H__
#define __ESPRESSO_OBSERVER_H__

#include "core/AutoUpdated.h"
#include "core/fn.h"

template<typename T>
class Observer: public AutoUpdated {
public:

  typedef T (*Provider)();
  typedef void (*Handler)(T);

  Observer(Provider p = 0)
  {
    if (p != 0) {
      this->observe(p);
    }
  }

  void observe(Provider p) {
    this->provider_ = p;
    this->lastValue_ = this->provider_();
  }

  void onChange(Handler h) {
    this->onChange_ = h;
  }

  void enable() {
    this->flags_[ACTIVE] = true;
  }

  void disable() {
    this->flags_[ACTIVE] = false;
  }

  bool isActive() {
    return this->flags_[ACTIVE];
  }

  void update() override {
    if (!this->flags_[ACTIVE] || this->provider_ == 0) {
      return;
    }
    const T currentValue = this->provider_();
    if (this->lastValue_ == currentValue) {
      return;
    }
    if (this->onChange_ != 0) {
      this->onChange_(currentValue);
    }
    this->lastValue_ = currentValue;
  }

protected:
  enum Flags { ACTIVE };
  bool flags_[4] = {true};
  T lastValue_;
  Provider provider_ = 0;
  Handler onChange_ = 0;
};

#endif
