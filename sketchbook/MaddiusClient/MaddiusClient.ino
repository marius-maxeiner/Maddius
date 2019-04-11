
#include <Wire.h> // I2C
#include <ClickEncoder.h>


// #include <TimerOne.h>
#define CHIPSET ARDUINO_NANO
#include <ControlPanel.h> // own libary

#define DEVMODE true


Button button1(12);
Button button2(13);
Button button3(14);
Button button4(15);
Button button5(16);
Button button6(17);
//Button button7(18);
//Button button8(19);


void setup() {
  // put your setup code here, to run once:
  if (DEVMODE) {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600); // start serial for output
  }

}

void loop() {
  short b1 = button1.update();
  short b2 = button2.update();
  short b3 = button4.update();
  short b4 = button4.update();
  short b5 = button5.update();
  short b6 = button6.update();
  //short b7 = button7.update();
  //short b8 = button8.update();
    Serial.print("A1 ");
    Serial.println(analogRead(18));
    Serial.print("A2 ");
    Serial.println(analogRead(19));

  if(button1._humanChanged){
    Serial.println("button1._humanChanged");
    Serial.println(b1);
    // usbMIDI.sendControlChange(64, b1, 1);
  }
  if(button2._humanChanged){
    Serial.println("button2._humanChanged");
    Serial.println(b2);
    // usbMIDI.sendControlChange(64, b2, 2);
  }
  if(button3._humanChanged){
    Serial.println("button3._humanChanged");
    Serial.println(b3);
    // usbMIDI.sendControlChange(64, b3, 3);
  }
  if(button4._humanChanged){
    Serial.println("button4._humanChanged");
    Serial.println(b4);
    // usbMIDI.sendControlChange(64, b4, 4);
  }
  if(button5._humanChanged){
    Serial.println("button5._humanChanged");
    Serial.println(b5);
    // usbMIDI.sendControlChange(65, b5, 5);
  }
  if(button6._humanChanged){
    Serial.println("button6._humanChanged");
    Serial.println(b6);
    // usbMIDI.sendControlChange(64, b6, 6);
  }
  /* if(button7._humanChanged){
    Serial.println("button7._humanChanged");
    Serial.println(b7);
    // usbMIDI.sendControlChange(64, b7, 7);
  }
  if(button8._humanChanged){
    Serial.println("button8._humanChanged");
    Serial.println(b8);
    // usbMIDI.sendControlChange(64, b8, 8);
  }*/


}
