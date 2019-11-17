#ifndef __YPS_CORE_H__
#define __YPS_CORE_H__

class Device;

namespace yps {
  unsigned long millis();
};

namespace __yps_internal {
  int _digitalRead(uint8_t pin);
  Device* _getRootDevice();
  void _clearRootDevice();
  Device* _getNextDevice(Device& d);
  void _callOnLoop(Device& d);
}

#endif
