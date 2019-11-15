#ifndef __YPS_DEVICE_H__
#define __YPS_DEVICE_H__

class InputDevice {
public:
  InputDevice() {
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
    if (YPS_ROOT_INPUTDEVICE == NULL) {
      YPS_ROOT_INPUTDEVICE = this;
      nextDevice = this;
      previousDevice = this;
    } else {
      previousDevice = YPS_ROOT_INPUTDEVICE->previousDevice;
      YPS_ROOT_INPUTDEVICE->previousDevice->nextDevice = this;
      nextDevice = YPS_ROOT_INPUTDEVICE;
      YPS_ROOT_INPUTDEVICE->previousDevice = this;
    }
  }

  void detach() {
    if (!isAttached()) {
      return;
    }
    previousDevice->nextDevice = nextDevice;
    nextDevice = NULL;
    if (YPS_ROOT_INPUTDEVICE == this) {
      YPS_ROOT_INPUTDEVICE = NULL;
    }
  }

  InputDevice* next() {
    return nextDevice;
  }

  static InputDevice* YPS_ROOT_INPUTDEVICE;

private:
  InputDevice* nextDevice = NULL;
  InputDevice* previousDevice = NULL;
};

#endif
