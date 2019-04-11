
#include <Wire.h> // I2C
#include <ClickEncoder.h>
// #include <TimerOne.h>
#define CHIPSET ARDUINO_NANO
#include <ControlPanel.h> // own libary

#define DEVMODE true


Button button1(2);

void setup() {
  // put your setup code here, to run once:
  if (DEVMODE) {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600); // start serial for output
  }

}

void loop() {
  short b1 = button1.update();
  if(b1 == 1){  
    int p1 = analogRead(24);
    int tone1 = map(p1, 0, 1023, 31, 4900);
    tone(8, tone1, 500);
  }else {
    noTone(8);
  }
  if(button1._humanChanged){
    Serial.println("button1._humanChanged");
    Serial.println(b1);
    // usbMIDI.sendControlChange(64, b1, 1);
  }
}
