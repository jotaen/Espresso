#ifndef __RDN_H__
#define __RDN_H__

#include "Virtuino.h"

namespace rdn {

  bool isValidPort(uint8_t port) {
    return port != NOT_A_PIN;
  }

  void pinModeUnchecked(uint8_t bit, uint8_t port, uint8_t mode) {
    Virtuino::__pinModes[port] = mode;
  }

  void digitalWriteUnchecked(uint8_t bit, uint8_t port, uint8_t val) {
    Virtuino::__digitalOutputs[port] = val;
  }

  int digitalReadUnchecked(uint8_t bit, uint8_t port)
  {
    return Virtuino::__digitalInputs[port];
  }

}

#endif
