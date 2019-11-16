#ifndef __YPS_CORE_H__
#define __YPS_CORE_H__

class Device;

class yps {
public:
  static unsigned long millis();
  static int digitalRead(uint8_t pin);

private:
  friend class Device;
  friend class World;

  static Device* rootDevice;
};

#endif
