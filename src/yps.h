#ifndef __YPS_CORE_H__
#define __YPS_CORE_H__

class Device;

class yps {
public:
  static unsigned long millis();

private:
  friend class Device;
  friend class World;

  static Device* rootDevice;
};

#endif
