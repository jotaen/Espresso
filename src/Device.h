#ifndef __YPS_DEVICE_H__
#define __YPS_DEVICE_H__

class Device {
public:
  Device();

  bool isAttached();

  void attach(bool status = true);

  void detach();

  Device* next();

private:
  Device* nextDevice = 0;
  Device* previousDevice = 0;
};

#endif
