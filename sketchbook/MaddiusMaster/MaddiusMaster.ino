//This is the Code for the Maddius Main Controller, built by Marius and Eddie.
//We hope you have fun editing and using this Code for yourself.



//________Including Library´s____________
#include <Wire.h> // I2C
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <ControlPanel.h>

//________Setting Defines________________
#define DEVMODE true

//________Setting Pins___________________
//MotorA motor1(3, 4, 2);
Button button1(49);
Button button2(50);
Button button3(51);
// Fader fader1(10, 30, new MotorA(3, 4, 2));
Fader fader1(10, 30, new MotorPWM(2, 3));
int pwmCircleCount = 0;
byte motorspeed = 0;

ClickEncoder* encoder;
int16_t last, value;

int16_t mouseTimeout = 0;

JoyStick* joy1;
void setup() {
  encoder = new ClickEncoder(A20, A19, A18);
  joy1 =  new JoyStick(A17,A16);
  if (DEVMODE) {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_BUILTIN, INPUT_PULLUP);
    pinMode(52, OUTPUT);
    // ___SERIAL_BEGIN____
    Serial.begin(57600);
    // Serial.println("Start Maddius Master");
  }

  // __Init Midi read functions__
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleAfterTouchPoly(myAfterTouchPoly);
  usbMIDI.setHandleControlChange(myControlChange);

  //fader1._valueTarget = 800;

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
}

void timerIsr() {
  encoder->service();
  
  if(mouseTimeout > 10){
    joy1->update();
    if(joy1->_humanChanged){
      Serial.print(" X: ");
      Serial.print(joy1->_xValue);
      Serial.print(" Y: ");
      Serial.println(joy1->_yValue);
      usbMIDI.sendControlChange(96, joy1->_xValue >> 3, 1);
      usbMIDI.sendControlChange(97, joy1->_yValue >> 3, 1);
    }
    mouseTimeout = 0;
  }
  mouseTimeout++;
}

void loop() {
  short f1 = fader1.update();

  
  short b1 = button1.update();
  short b2 = button2.update();
  short b3 = button3.update();
  byte val = f1 / 8;
  if (DEVMODE) {
      if(fader1._humanChanged){
        Serial.println("_humanChanged");
        Serial.println(f1);
        usbMIDI.sendControlChange(12, val, 1);
      }
      if(button1._humanChanged){
        Serial.println("button1._humanChanged");
        Serial.println(b1);
        usbMIDI.sendControlChange(64, b1, 1);
      }
      if(button2._humanChanged){
        Serial.println("button2._humanChanged");
        Serial.println(b2);
        usbMIDI.sendControlChange(65, b2, 1);
      }
      if(button3._humanChanged){
        Serial.println("button2._humanChanged");
        Serial.println(b3);
        usbMIDI.sendControlChange(66, b3, 1);
      }
  }

  value += encoder->getValue();
  
  if (value != last) {
    last = value;
    Serial.print("Encoder Value: ");
    Serial.println(value);
  }

  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    Serial.print("Button: ");
    #define VERBOSECASE(label) case label: Serial.println(#label); break;
    switch (b) {
      VERBOSECASE(ClickEncoder::Pressed);
      VERBOSECASE(ClickEncoder::Held)
      VERBOSECASE(ClickEncoder::Released)
      VERBOSECASE(ClickEncoder::Clicked)
      case ClickEncoder::DoubleClicked:
          Serial.println("ClickEncoder::DoubleClicked");
          encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
          Serial.print("  Acceleration is ");
          Serial.println((encoder->getAccelerationEnabled()) ? "enabled" : "disabled");
        break;
    }
  }
  //int poti = analogRead(A11);
  //Serial.println(poti >> 2);
  // analogWrite(2, poti >> 2);
  
  /*int btn = digitalRead(56);
  int x = analogRead(33);
  int y = analogRead(34);
  Serial.print("B:");
  Serial.print(btn);
  Serial.print(" X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.println(y);*/

  // Serial.println(a1);
  // Serial.println(pos[poscount]);
  // Read MIDI from USB 
  while (usbMIDI.read()) {
    // read & ignore incoming messages
    //Serial.println("read");
    //Serial.println(usbMIDI.getType());
    //Serial.println(usbMIDI.getChannel());
  }
 }

 void myNoteOn(byte channel, byte note, byte velocity){
  if (DEVMODE) {
    Serial.println("myNoteOn");
    Serial.println(channel);
    Serial.println(note);
    Serial.println(velocity);
  }
 }
 void myNoteOff(byte channel, byte note, byte velocity){
  if (DEVMODE) {
    Serial.println("myNoteOff");
    Serial.println(channel);
    Serial.println(note);
    Serial.println(velocity);
  }
 }
 void myAfterTouchPoly(byte channel, byte note, byte velocity){
  if (DEVMODE) {
    Serial.println("myAfterTouchPoly");
    Serial.println(channel);
    Serial.println(note);
    Serial.println(velocity);
  }
 }
 void myControlChange(byte channel, byte control, byte value){
  if (DEVMODE) {
    Serial.println("myControlChange");
    Serial.println(channel);
    Serial.println(control);
    Serial.println(value);
  }
  if(control == 12){
    fader1._valueTarget = value * 8;
  }
  if(control == 66){
    if(value == 127){
      pinMode(52, INPUT_PULLUP);
    }else {
      pinMode(52, INPUT_PULLDOWN);
    }
  }
 }
