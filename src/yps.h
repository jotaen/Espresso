#ifndef __YPS_CORE_H__
#define __YPS_CORE_H__

class Device;
class World;

class yps {
public:
  static void reset();

  static Device* next(Device& d);

  static void callOnLoop(Device& d);

  static unsigned long millis();

private:
  friend class Device;
  friend class World;
  static Device* rootDevice;
};

#endif
