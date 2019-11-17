#include "src/yps.h"
#include "src/Actor.h"
#include "src/Timer.h"

void onSetup();

int main() {
  onSetup();
  Device* deviceIt = yps::rootDevice;
  while (true) {
    while {
      (*deviceIt).onLoop();
      deviceIt = (*deviceIt).nextDevice;
    } while (deviceIt != yps::rootDevice);
  }
}
