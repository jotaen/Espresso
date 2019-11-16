#ifndef __YPS_DEVICE_H__
#define __YPS_DEVICE_H__

class Device {
public:
  Device();
  ~Device();

protected:
  virtual void onLoop() = 0;

private:
  friend class _core;
  Device* nextDevice = 0;
  Device* previousDevice = 0;
};

#endif
