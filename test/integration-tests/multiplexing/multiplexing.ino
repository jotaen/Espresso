#include <Espresso.h>

DigitalInput row1(1);
DigitalInput row2(2);
DigitalInput row3(3);
DigitalInput row4(4);
DigitalInput col1(5);
DigitalInput col2(6);
DigitalInput col3(7);

Observer button1(     [](){ return row1.isHigh() && col1.isHigh(); });
Observer button2(     [](){ return row1.isHigh() && col2.isHigh(); });
Observer button3(     [](){ return row1.isHigh() && col3.isHigh(); });
Observer button4(     [](){ return row2.isHigh() && col1.isHigh(); });
Observer button5(     [](){ return row2.isHigh() && col2.isHigh(); });
Observer button6(     [](){ return row2.isHigh() && col3.isHigh(); });
Observer button7(     [](){ return row3.isHigh() && col1.isHigh(); });
Observer button8(     [](){ return row3.isHigh() && col2.isHigh(); });
Observer button9(     [](){ return row3.isHigh() && col3.isHigh(); });
Observer buttonCall(  [](){ return row4.isHigh() && col1.isHigh(); });
Observer button0(     [](){ return row4.isHigh() && col2.isHigh(); });
Observer buttonHangUp([](){ return row4.isHigh() && col3.isHigh(); });

String number;

void onSetup() {
  button1.onTrue([](){ number += "1"; });
  button2.onTrue([](){ number += "2"; });
  button3.onTrue([](){ number += "3"; });
  button4.onTrue([](){ number += "4"; });
  button5.onTrue([](){ number += "5"; });
  button6.onTrue([](){ number += "6"; });
  button7.onTrue([](){ number += "7"; });
  button8.onTrue([](){ number += "8"; });
  button9.onTrue([](){ number += "9"; });
  button0.onTrue([](){ number += "0"; });
}
