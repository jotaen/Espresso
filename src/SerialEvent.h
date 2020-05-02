#ifndef __ESPRESSO_SERIALEVENT_H__
#define __ESPRESSO_SERIALEVENT_H__

#include "core/AutoUpdated.h"
#include "core/fn.h"

/**
 * Handler for Serial Events
 */
class SerialEvent: public AutoUpdated {
public:
  SerialEvent(uint8_t serialPort = 0)
  : serialPort_(serialPort) {}

  /**
   * Register handler function
   */
  void onEvent(fn::Handler h) {
    this->handler_ = h;
  }

  void update() {
    if (!rdn::checkForSerialEvent(this->serialPort_)) {
      return;
    }
    fn::invoke(this->handler_);
  }

protected:
  uint8_t serialPort_;
  fn::Handler handler_ = 0;
};

#endif
