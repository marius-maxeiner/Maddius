<<<<<<< HEAD
/* Belegung	Pin Name	Pin Number	Spice Number
	VBAT	1	1
	5V	2	2
	USBD2-	3	3
	USBD2+	4	4
	USBD1-	5	5
	USBD1+	6	6
Fader 5	A10	7	7
Fader 6	A11	8	8
	GND	9	9
Btn 1	0	10	10
Btn 2	1	11	11
Btn LED 1	2	12	12
Btn LED 2	3	13	13
Btn LED 3	4	14	14
Btn LED 4	5	15	15
Btn LED 5	6	16	16
Btn LED 6	7	17	17
Btn LED 7	8	18	18
Btn LED 8	9	19	19
Btn LED 9	10	20	20
Motor 1 B	11	21	21
Motor 1 A	12	22	22
Motor 5 B	40	23	23
Motor 2 B	24	24	24
Motor 3 B	25	25	25
Motor 3 A	26	26	26
Motor 4 A	27	27	27
Motor 4 B	28	28	28
Touch 8	29	29	29
Touch 9	30	30	30
Fader 1	31/A12	31	31
Fader 2	32/A13	32	32
Motor 5 A	41	33	33
Motor 6 A	42	34	34
Motor 6 B	43	35	35
Motor 7 B	44	36	36
Motor 7 B	45	37	37
Motor 8 A	46	38	38
Motor 8 B	47	39	39
Motor 9 B	48	40	40
Btn 3	49/A23	41	41
Btn 4	50/A24	42	42
Motor 9 A	51	43	43
Btn 5	52	44	44
Btn 6	53	45	45
Btn 7	54	46	46
Btn 8	55	47	47
I2C	56	48	48
Standby	33/A14	49	49
Motor 2 A	34/A15	50	50
	35/A16	51	51
Motor Speed	36/A17	52	52
I2C	37/A18	53	53
I2C	38/A19	54	54
Fader 7	39/A20	55	55
Fader 3	A21	56	56
Fader 4	A22	57	57
I2C	57	58	58
Power/Sys LED	13 (LED)	59	59
Fader 8	14/A0	60	60
Touch 1	15/A1	61	61
Touch 2	16/A2	62	62
Touch 3	17/A3	63	63
Touch 4	18/A4	64	64
Touch 5	19/A5	65	65
Fader 9	20/A6	66	66
Btn 9	21/A7	67	67
Touch 6	22/A8	68	68
Touch 7	23/A9	69	69
	3V3	70	70
	AGND	71	71
Main Power	VIN	72	72
	GND	73	73
	VUSB	74	74
	PRGM	75	75
	RESET	76	76
	AREF	77	77
	DBGEN	78	78
	SWCLK	79	79
	SWDIO	80	80
	MT1	81	81
	MT2	82	82
*/
=======
//This is the Code for the Maddius Main Controller, built by Marius and Eddie.
//We hope you have fun editing and using this Code for yourself.

>>>>>>> 7a19cae50ffcc8ba62d0dede8335053ce0ca0dc0


//________Including Library´s____________
#include <Wire.h> // I2C
// #include <ClickEncoder.h>
#include <TimerOne.h>
#include <ControlPanel.h>

//________Setting Defines________________
#define DEVMODE true

//________Setting Pins___________________
//MotorA motor1(3, 4, 2);

// Button Digi/LED PWM // 
// B1 0 / 2
Button button1(0);
// B2 1 / 3
Button button2(1);
/*// B3 55 / 4
Button button3(55);
// B4 14 / 31
Button button4(14);
// B5 35 / 6 // A16 / 
Button button5(35);
// B6 34 / 7 // A15 /
Button button6(34);
// B7 39 / 8 // A20
Button button7(39);
// B8 49 / 9 // A23
Button button8(49);
// B9 50 / 10 // A24
Button button9(50);*/

// Motor

// FADER Analog / Touch
// F1
Fader fader1(31, 15, new MotorB(11, 12, 36, 33)); // , new MotorPWM(2, 3)
// F2
Fader fader2(32, 16, new MotorB(34, 24, 36, 33));
// F3
Fader fader3(A21, 17, new MotorB(25, 26, 36, 33));
// F4
Fader fader4(A22, 18, new MotorB(27, 28, 36, 33));
// F5
Fader fader5(A10, 19, new MotorB(40, 41, 36, 33));
// F6
Fader fader6(A11, 22, new MotorB(42, 43, 36, 33));
// F7 
Fader fader7(39, 23, new MotorB(44, 45, 36, 33));
// F8
Fader fader8(14, 29, new MotorB(46, 47, 36, 33));
// F9
Fader fader9(20, 30, new MotorB(48, 51, 36, 33));

// Motoren PWM: 52
// M1 12 / 11

// Fader 1 fader1(10, 30, new MotorA(3, 4, 2));

// Fader fader2(A2, A3); // , new MotorPWM(4, 5)



//int pwmCircleCount = 0;
//byte motorspeed = 0;

// ClickEncoder* encoder;
// int16_t last, value;

// int16_t mouseTimeout = 0;

// JoyStick* joy1;
void setup() {
<<<<<<< HEAD
  // encoder = new ClickEncoder(A20, A19, A18);
  // joy1 =  new JoyStick(A17,A16);
  // put your setup code here, to run once
  if (DEVMODE) {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_BUILTIN, INPUT_PULLUP);
    // Serial.begin(57600); // start serial for output
=======
  encoder = new ClickEncoder(A20, A19, A18);
  joy1 =  new JoyStick(A17,A16);
  if (DEVMODE) {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_BUILTIN, INPUT_PULLUP);
    pinMode(52, OUTPUT);
    // ___SERIAL_BEGIN____
    Serial.begin(57600);
>>>>>>> 7a19cae50ffcc8ba62d0dede8335053ce0ca0dc0
    // Serial.println("Start Maddius Master");
  }

  // __Init Midi read functions__
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleAfterTouchPoly(myAfterTouchPoly);
  usbMIDI.setHandleControlChange(myControlChange);

  //fader1._valueTarget = 800;

  // Timer1.initialize(1000);
  // Timer1.attachInterrupt(timerIsr);
  // Motoren PWM: 52
// M1 12 / 11
  /* byte _motorUpIOPin = 11;
   byte _motorDownIOPin = 12;
   byte _motorSpeedPWM = 52;
  delay(1000);
  // Motor Test
  pinMode(_motorUpIOPin, OUTPUT);
  pinMode(_motorDownIOPin, OUTPUT);
  analogWrite(_motorSpeedPWM , 150);
  delay(1000);
  digitalWrite(_motorUpIOPin, HIGH);
  digitalWrite(_motorDownIOPin, LOW);
  delay(1000);
  digitalWrite(_motorUpIOPin, LOW);
  digitalWrite(_motorDownIOPin, HIGH);
  delay(1000);
  digitalWrite(_motorUpIOPin, HIGH);
  digitalWrite(_motorDownIOPin, LOW);
  delay(1000);
  digitalWrite(_motorUpIOPin, LOW);
  digitalWrite(_motorDownIOPin, HIGH);
  delay(1000);*/



}

/* void timerIsr() {
  // encoder->service();
  
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
} */
void loop() {

  
  // BUTTON UPDATE
  short b1 = button1.update();
  short b2 = button2.update();
  /*short b3 = button3.update();
  short b4 = button4.update();
  short b5 = button5.update();
  short b6 = button6.update();
  short b7 = button7.update();
  short b8 = button8.update();
  short b9 = button9.update();*/

  // FADER UPDATE




  short f1 = fader1.update();
          //Serial.println("f1_humanChanged");
        //Serial.println(fader1.readTouch());



  short f2 = fader2.update();
  short f3 = fader3.update();
  short f4 = fader4.update();
  short f5 = fader5.update();
  short f6 = fader6.update();
  short f7 = fader7.update();
  short f8 = fader8.update();
  short f9 = fader9.update();

  

  byte val1 = f1 / 8;
  byte val2 = f2 / 8;
  byte val3 = f3 / 8;
  byte val4 = f4 / 8;
  byte val5 = f5 / 8;
  byte val6 = f6 / 8;
  byte val7 = f7 / 8;
  byte val8 = f8 / 8;
  byte val9 = f9 / 8;
  
  /*if (DEVMODE) {
      //Serial.println(fader1.readAnalog());
      //Serial.println(touchRead(15));

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
      /*if(button3._humanChanged){
        Serial.println("button3._humanChanged");
        Serial.println(b3);
        usbMIDI.sendControlChange(66, b3, 1);
      }
      if(button4._humanChanged){
        Serial.println("button4._humanChanged");
        Serial.println(b4);
        usbMIDI.sendControlChange(67, b4, 1);
      }
      if(button5._humanChanged){
        Serial.println("button5._humanChanged");
        Serial.println(b5);
        usbMIDI.sendControlChange(68, b5, 1);
      }
      if(button6._humanChanged){
        Serial.println("button6._humanChanged");
        Serial.println(b6);
        usbMIDI.sendControlChange(69, b6, 1);
      }
     if(button7._humanChanged){
        Serial.println("button7._humanChanged");
        Serial.println(b7);
        usbMIDI.sendControlChange(70, b7, 1);
      }
      if(button8._humanChanged){
        Serial.println("button8._humanChanged");
        Serial.println(b8);
        usbMIDI.sendControlChange(71, b8, 1);
      }
      if(button9._humanChanged){
        Serial.println("button9._humanChanged");
        Serial.println(b9);
        usbMIDI.sendControlChange(72, b9, 1);
        _humanChanged = false;
      }*/
// Serial.print("T1: ");
// Serial.println(fader1.readTouch());
// Serial.print("F1: ");
//Serial.println(fader1.readAnalog());


      // FADER 
      /*if(fader1._humanChanged){
        Serial.println("f1_humanChanged");
        Serial.println(fader1.readTouch());
        // Serial.println(f1);
        Serial.println(fader1.readAnalog());
        usbMIDI.sendControlChange(12, val1, 1);
      }
     if(fader2._humanChanged){
        Serial.println("f2_humanChanged");
        Serial.println(fader2.readTouch());
        Serial.println(f2);
        Serial.println(fader2._valueTarget);
        usbMIDI.sendControlChange(13, val2, 1);
      }
      if(fader3._humanChanged){
        Serial.println("f3_humanChanged");
        Serial.println(fader3.readTouch());
        Serial.println(f3);
        Serial.println(fader3._valueTarget);
        usbMIDI.sendControlChange(14, val3, 1);
      }
      if(fader4._humanChanged){
        Serial.println("f4_humanChanged");
        Serial.println(fader4.readTouch());
        Serial.println(f4);
        Serial.println(fader4._valueTarget);
        usbMIDI.sendControlChange(15, val4, 1);
      }
      if(fader5._humanChanged){
        Serial.println("f5_humanChanged");
        Serial.println(fader5.readTouch());
        Serial.println(f5);
        Serial.println(fader5._valueTarget);
        usbMIDI.sendControlChange(16, val5, 1);
      }
      if(fader6._humanChanged){
        Serial.println("f6_humanChanged");
        Serial.println(fader6.readTouch());
        Serial.println(f6);
        Serial.println(fader6._valueTarget);
        usbMIDI.sendControlChange(17, val6, 1);
      }
      if(fader7._humanChanged){
        Serial.println("f7_humanChanged");
        Serial.println(fader7.readTouch());
        Serial.println(f7);
        Serial.println(fader7._valueTarget);
        usbMIDI.sendControlChange(18, val7, 1);
      }
      if(fader8._humanChanged){
        Serial.println("f8_humanChanged");
        Serial.println(fader8.readTouch());
        Serial.println(f8);
        Serial.println(fader8._valueTarget);
        usbMIDI.sendControlChange(19, val8, 1);
      }
      if(fader9._humanChanged){
        Serial.println("f9_humanChanged");
        Serial.println(fader9.readTouch());
        Serial.println(f9);
        Serial.println(fader9._valueTarget);
        usbMIDI.sendControlChange(20, val9, 1);
      }
  }

  // value += encoder->getValue();
  
  /*if (value != last) {
    last = value;
    Serial.print("Encoder Value: ");
    Serial.println(value);
  }*/

  /* ClickEncoder::Button b = encoder->getButton();
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
  } */
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
  if(fader1._humanChanged){
  usbMIDI.sendControlChange(12, val1, 1);
  }
  if(fader2._humanChanged){
  usbMIDI.sendControlChange(13, val2, 1);
  }
  if(fader3._humanChanged){
  usbMIDI.sendControlChange(14, val3, 1);
  }
  if(fader4._humanChanged){
  usbMIDI.sendControlChange(15, val4, 1);
  }
  if(fader5._humanChanged){
  usbMIDI.sendControlChange(16, val5, 1);
  }
  if(fader6._humanChanged){
  usbMIDI.sendControlChange(17, val6, 1);
  }
  if(fader7._humanChanged){
  usbMIDI.sendControlChange(18, val7, 1);
  }
  if(fader8._humanChanged){
  usbMIDI.sendControlChange(19, val8, 1);
  }
  if(fader9._humanChanged){
  usbMIDI.sendControlChange(20, val9, 1);
  }


  // Serial.println(a1);
  // Serial.println(pos[poscount]);
  // Read MIDI from USB 
  while (usbMIDI.read()) {
    // read & ignore incoming messages
    Serial.println("read");
    Serial.println(usbMIDI.getType());
    Serial.println(usbMIDI.getChannel());
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
  if(control == 13){
    fader2._valueTarget = value * 8;
  }
  if(control == 14){
    fader3._valueTarget = value * 8;
  }
  if(control == 15){
    fader4._valueTarget = value * 8;
  }
  if(control == 16){
    fader5._valueTarget = value * 8;
  }
  if(control == 17){
    fader6._valueTarget = value * 8;
  }
  if(control == 18){
    fader7._valueTarget = value * 8;
  }
  if(control == 19){
    fader8._valueTarget = value * 8;
  }
  if(control == 20){
    fader9._valueTarget = value * 8;
  }
 }
