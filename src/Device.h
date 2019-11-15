#ifndef __YPS_DEVICE_H__
#define __YPS_DEVICE_H__

class Device {
public:
  Device();
  ~Device();

  bool isAttached();

  void attach(bool status = true);

  void detach();

private:
  friend class _core;
  Device* nextDevice = 0;
  Device* previousDevice = 0;
};

#endif
