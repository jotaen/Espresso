#ifndef __YPS_ACTOR_H__
#define __YPS_ACTOR_H__

#include "Device.h"

class Actor: public Device {

  typedef bool (*Predicate)();
  typedef void (*Handler)();

public:
  Actor(Predicate p, Handler h)
  : predicate(p), handler(h)
  {}

protected:
  void onLoop() {
    if (predicate()) {
      handler();
    }
  }

private:
  Predicate predicate;
  Handler handler;
};

#endif
