#include <Espresso.h>

enum KEY
{
  key0 = 0,
  key1,
  key2,
  key3,
  key4,
  key5,
  key6,
  key7,
  key8,
  key9,
  cancel,
  dial,
  none
};

DigitalInput row1(1);
DigitalInput row2(2);
DigitalInput row3(3);
DigitalInput row4(4);
DigitalInput col1(5);
DigitalInput col2(6);
DigitalInput col3(7);
Observer<KEY> keypad;

String number;

void onSetup() {
  keypad.observe([]() -> KEY {
    if (row1.isHigh() && col1.isHigh()) return key1;
    if (row1.isHigh() && col2.isHigh()) return key2;
    if (row1.isHigh() && col3.isHigh()) return key3;
    if (row2.isHigh() && col1.isHigh()) return key4;
    if (row2.isHigh() && col2.isHigh()) return key5;
    if (row2.isHigh() && col3.isHigh()) return key6;
    if (row3.isHigh() && col1.isHigh()) return key7;
    if (row3.isHigh() && col2.isHigh()) return key8;
    if (row3.isHigh() && col3.isHigh()) return key9;
    if (row4.isHigh() && col1.isHigh()) return cancel;
    if (row4.isHigh() && col2.isHigh()) return key0;
    if (row4.isHigh() && col3.isHigh()) return dial;
    return none;
  });
  keypad.onChange([](KEY key) {
    if (key >= key0 && key <= key9) {
      number += std::to_string(key);
    } else if (key == cancel) {
      number = "";
    }
  });
}
