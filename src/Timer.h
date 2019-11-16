#ifndef __YPS_TIMER_H__
#define __YPS_TIMER_H__

// #include "yps.h"

class Timer: public Device {
  
  typedef void (*Handler)();

public:
  Timer(Handler h)
  : handler(h)
  {}

protected:
  void onLoop() {}
  Handler handler;
};

#endif
