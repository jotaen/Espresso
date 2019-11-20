#ifndef __ESPRESSO_AUTOUPDATED_H__
#define __ESPRESSO_AUTOUPDATED_H__

namespace Virtuino {
  void clear();
}

class AutoUpdated {
public:
  AutoUpdated() {
    if (root == 0) {
      root = this;
      this->next = this;
    } else {
      AutoUpdated* last = root;
      while (last->next != root) {
        last = last->next;
      }
      last->next = this;
      this->next = root;
    }
  }

  virtual ~AutoUpdated() {
    AutoUpdated* predecessor = root;
    while (predecessor->next != this) {
      predecessor = predecessor->next;
    }
    predecessor->next = this->next;
    if (root == this) {
      root = 0;
    }
  }

  virtual void update() = 0;

protected:
  friend void loop();
  friend void Virtuino::clear();

  static AutoUpdated* root;
  AutoUpdated* next = 0;
};

AutoUpdated* AutoUpdated::root = 0;

#endif
