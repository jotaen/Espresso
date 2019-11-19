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
      this->prev = this;
    } else {
      this->prev = root->prev;
      root->prev->next = this;
      this->next = root;
      root->prev = this;
    }
  }

  virtual ~AutoUpdated() {
    this->prev->next = next;
    this->next = 0;
    if (root == this) {
      root = 0;
    }
  }

protected:
  friend void Virtuino::clear();
  friend void loop();

  virtual void onLoop() = 0;

  static AutoUpdated* root;
  AutoUpdated* next = 0;
  AutoUpdated* prev = 0;
};

#endif
