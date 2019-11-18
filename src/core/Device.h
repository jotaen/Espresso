#ifndef __ESPRESSO_DEVICE_H__
#define __ESPRESSO_DEVICE_H__

namespace Virtuino {
  void clear();
}

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

  virtual ~Device() {
    this->previousDevice->nextDevice = nextDevice;
    this->nextDevice = 0;
    if (rootDevice == this) {
      rootDevice = 0;
    }
  }

protected:
  friend void Virtuino::clear();
  friend void loop();

  virtual void onLoop() = 0;

  static Device* rootDevice;
  Device* nextDevice = 0;
  Device* previousDevice = 0;
};

#endif
