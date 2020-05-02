#ifndef __ESPRESSO_AUTOUPDATED_H__
#define __ESPRESSO_AUTOUPDATED_H__

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

  /**
   * Triggers internal update
   * This is safe to do at any time, but it usually is not necessary,
   * because the Event Loop takes care of doing it regularly
   */
  virtual void update() = 0;

  static AutoUpdated* getRoot() {
    return root;
  }

protected:
  friend void loop();

  static AutoUpdated* root;
  AutoUpdated* next = 0;
};

AutoUpdated* AutoUpdated::root = 0;

#endif
