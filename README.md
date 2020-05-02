# ☕️ Espresso

Espresso is an experimental framework for Arduino. It allows to write sketches in an object-oriented and high-level-like way, while still being as performant as possible. Beyond that, it comes with a testing setup that allows you to develop and verify sketches before even uploading them to the board. [Read more on the ideas behind it on my blog](https://www.jotaen.net/e7ewR).

## Usage

Clone this repository into the library path that is configured in your Arduino library. Use it in your sketch by putting `#include "Espresso"` at the top, which pulls in all available classes.

You can see Espresso in action by checking out the [integration tests](test/integration-tests), or see the following example:

```cpp
#include <Espresso.h>

const unsigned long duration = 1000;

DigitalInput button(7);
DigitalOutput led(13);
Timer ledTimer;
Observer<bool> buttonObserver;

void onSetup() {
  buttonObserver.observe([](){ return button.isHigh(); });
  buttonObserver.onChange([](bool isHigh){
    if (isHigh) {
      led.write(HIGH);
      ledTimer.runOnce(duration);
    }
  });
  ledTimer.onTrigger([](){ led.write(LOW); });
}
```

## Testing

The provided testing runtime is called “Virtuino” (think of it as “virtual Arduino”). It allows you to artifically manipulate states on the board and then make testing assertions on whether your sketch responds to these states as you would expect it.

You can use whatever assertion mechanism you like. Simply create a .cpp file that includes Virtuino and your sketch under test, like so:

```cpp
#include <assert.h>
#include <Virtuino.h>
#include "my-sketch.ino"

Virtuino virtuino;

virtuino.setDigitalInput(5, HIGH);
assert(myPin.value() == LOW);
virtuino.elapseMillis(200);
assert(myPin.value() == HIGH);
```

Then compile the test file with the following options and run it to see the output:

```bash
g++ -std=c++11 --include-directory=/PATH_TO_ESPRESSO/lib/virtuino
```

Other compilers should do it as well, of course. Keep in mind, though, that the Arduino compiler is configured to use the 2011 standard of C++.
