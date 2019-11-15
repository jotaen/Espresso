#ifndef __YPS_DEVICE_H__
#define __YPS_DEVICE_H__

class Device {
public:
  Device() {
    attach();
  }

  bool isAttached() {
    return nextDevice != NULL;
  }

  void attach(bool status = true) {
    if (!status) {
      detach();
      return;
    }
    if (isAttached()) {
      return;
    }
    if (YPS_ROOT_DEVICE == NULL) {
      YPS_ROOT_DEVICE = this;
      nextDevice = this;
      previousDevice = this;
    } else {
      previousDevice = YPS_ROOT_DEVICE->previousDevice;
      YPS_ROOT_DEVICE->previousDevice->nextDevice = this;
      nextDevice = YPS_ROOT_DEVICE;
      YPS_ROOT_DEVICE->previousDevice = this;
    }
  }

  void detach() {
    if (!isAttached()) {
      return;
    }
    previousDevice->nextDevice = nextDevice;
    nextDevice = NULL;
    if (YPS_ROOT_DEVICE == this) {
      YPS_ROOT_DEVICE = NULL;
    }
  }

  Device* next() {
    return nextDevice;
  }

  static Device* YPS_ROOT_DEVICE;

private:
  Device* nextDevice = NULL;
  Device* previousDevice = NULL;
};

#endif
