#define CATCH_CONFIG_MAIN
#include "../test.h"
#include "../yps.h"

DigitalInput button = DigitalInput(4);
bool led = false;
unsigned long frequency = 100;
Timer ledBlinker = Timer([](){ led = !led; });
Actor onButtonHigh = Actor(
  []()->bool { return button.isHigh(); },
  [](){ if (!ledBlinker.isActive()) {ledBlinker.runMillis(frequency);} }
);
Actor onButtonLow = Actor(
  []()->bool { return button.isLow(); },
  [](){ ledBlinker.stop(); led = false; }
);

TEST_CASE("LED starts blinking while button is pressed", "[BlinkButton]") {
  World::setDigitalInput(4, HIGH);
  World::settle();
  REQUIRE(led == false);
  World::elapseMillis(frequency);
  REQUIRE(led == true);
  World::elapseMillis(frequency);
  REQUIRE(led == false);
  World::elapseMillis(frequency);
  REQUIRE(led == true);
}

TEST_CASE("LED turns off when button is released", "[BlinkButton]") {
  World::setDigitalInput(4, LOW);
  World::settle();
  REQUIRE(led == false);
}
