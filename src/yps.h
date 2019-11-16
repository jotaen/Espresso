#ifndef __YPS_CORE_H__
#define __YPS_CORE_H__

class Device;

class yps {
public:
  static void reset();

  static Device* next(Device& d);

  static void callOnLoop(Device& d);

  static Device* rootDevice;
};

#endif
