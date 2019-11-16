#ifndef __YPS_UTILS_H_
#define __YPS_UTILS_H_

bool alwaysTrue() { return true; }

bool alwaysFalse() { return false; }

void noop() {}

/**
 *  Call spy for testing purpose
 *  This is one global instance, don’t forget to reset!
 */
namespace callspy {

  struct {
    bool hasBeenCalled;
    int count;
  } reporter;

  void Void() {
    reporter.hasBeenCalled = true;
    reporter.count++;
  }

  void reset() {
    reporter.hasBeenCalled = false;
    reporter.count = 0;
  }

}

#endif
