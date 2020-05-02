#ifndef __ESPRESSO_OBSERVER_H__
#define __ESPRESSO_OBSERVER_H__

#include "core/AutoUpdated.h"
#include "core/fn.h"

/**
 * Observe any value and trigger callback if that value changes
 */
template<typename T>
class Observer: public AutoUpdated {
public:

  typedef T (*Provider)();
  typedef void (*Handler)(T);

  /**
   * Provider (optional): a function that provides the value to observe
   */
  Observer(Provider p = 0)
  {
    if (p != 0) {
      this->observe(p);
    }
  }

  /**
   * A function that provides the value to observe
   */
  void observe(Provider p) {
    this->provider_ = p;
    this->lastValue_ = this->provider_();
  }

  /**
   * A handler that is supposed to be triggered if the value changes
   */
  void onChange(Handler h) {
    this->onChange_ = h;
  }

  /**
   * Resume callback invocation (if applicable)
   */
  void enable() {
    this->flags_[ACTIVE] = true;
  }

  /**
   * Suspend callback invocation
   */
  void disable() {
    this->flags_[ACTIVE] = false;
  }

  /**
   * Check whether object is enabled
   */
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
