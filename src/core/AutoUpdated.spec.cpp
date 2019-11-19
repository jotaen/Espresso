#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Virtuino.h>
#include "AutoUpdated.h"
#include "../util/callspy.h"

class AutoUpdated_: public AutoUpdated {
public:
  AutoUpdated* getNext() {
    return this->next;
  }
protected:
  void onLoop() {}
};

TEST_CASE("[AutoUpdated]") {

  Virtuino::clear();

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
    AutoUpdated_ au2 = AutoUpdated_();
    REQUIRE(au2.getNext() == &au2);
  }

}