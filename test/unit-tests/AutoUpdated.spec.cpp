#include "../../src/core/AutoUpdated.h"

struct AutoUpdated_: public AutoUpdated {
  AutoUpdated* getNext() { return this->next; }
  void update() {}
};

TEST_CASE("[AutoUpdated]") {

  Virtuino virtuino(Virtuino::DESTROY);

  SECTION("A single active AU-object points to itself") {
    AutoUpdated_ au = AutoUpdated_();
    REQUIRE(au.getNext() == &au);
  }

  SECTION("AU-objects point to each other subsequent order") {
    AutoUpdated_ au1 = AutoUpdated_();
    AutoUpdated_ au2 = AutoUpdated_();
    AutoUpdated_ au3 = AutoUpdated_();
    REQUIRE(au1.getNext() == &au2);
    REQUIRE(au2.getNext() == &au3);
    REQUIRE(au3.getNext() == &au1);
  }

  SECTION("A destroyed AU-object is no longer referenced") {
    AutoUpdated_ au1 = AutoUpdated_();
    AutoUpdated_ au2 = AutoUpdated_();
    {
      AutoUpdated_ au3 = AutoUpdated_();
      REQUIRE(au1.getNext() == &au2);
      REQUIRE(au2.getNext() == &au3);
      REQUIRE(au3.getNext() == &au1);
    }
    REQUIRE(au1.getNext() == &au2);
    REQUIRE(au2.getNext() == &au1);
  }

  SECTION("Destroying the last (or: only) AU-objects cleans up properly") {
    {
      AutoUpdated_ au1 = AutoUpdated_();
    }
    REQUIRE(AutoUpdated::getRoot() == 0);
  }

  SECTION("The root AU-object gets properly set according to AU lifecycles") {
    virtuino.flush();
    REQUIRE(AutoUpdated::getRoot() == 0);
    {
      AutoUpdated_ au1 = AutoUpdated_();
      virtuino.flush();
      REQUIRE(AutoUpdated::getRoot() == &au1);
      AutoUpdated_ au2 = AutoUpdated_();
      virtuino.flush();
      REQUIRE(AutoUpdated::getRoot() == &au1);
    }
    virtuino.flush();
    REQUIRE(AutoUpdated::getRoot() == 0);
  }

}
