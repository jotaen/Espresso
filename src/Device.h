#ifndef __YPS_DEVICE_H__
#define __YPS_DEVICE_H__

class Device {
public:
  Device() {
    if (rootDevice == 0) {
      rootDevice = this;
      this->nextDevice = this;
      this->previousDevice = this;
    } else {
      this->previousDevice = rootDevice->previousDevice;
      rootDevice->previousDevice->nextDevice = this;
      this->nextDevice = rootDevice;
      rootDevice->previousDevice = this;
    }
  }

  ~Device() {
    this->previousDevice->nextDevice = nextDevice;
    this->nextDevice = 0;
    if (rootDevice == this) {
      rootDevice = 0;
    }
  }

  static Device* next(const Device& d) {
    return d.nextDevice;
  }

  static void clearRoot() {
    Device::rootDevice = 0;
  }

  static void loopOnce() {
    Device* deviceIt = Device::rootDevice;
    do {
      (*deviceIt).onLoop();
      deviceIt = (*deviceIt).nextDevice;
    } while (deviceIt != Device::rootDevice);
  }

protected:
  virtual void onLoop() = 0;
  static Device* rootDevice;
  Device* nextDevice = 0;
  Device* previousDevice = 0;
};

#endif
