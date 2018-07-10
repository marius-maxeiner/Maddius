#include <OSCBundle.h>
#include <OSCData.h>
#include <SLIPEncodedUSBSerial.h>
#include <OSCTiming.h>
#include <OSCMessage.h>
#include <OSCBoards.h>
#include <OSCMatch.h>
#include <SLIPEncodedSerial.h>

#include <Wire.h>

#include <ControlPanel.h>

#include <CapacitiveSensor.h> //Library for fader touch sensitivity

#define DEVMODE true 
#define CHANNELCOUNT 3

int motorSpeedPin = 4;
int motorVorPin = 3;
int motorZurPin = 2;
int fadVal = 0;
int fadVal2 = 0;
int fadVal3 = 0;
int motorSpeed = 0;
int counter = 0;



// Control Panel Self
Control cp1l[] = {
  {2, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {3, 12, 2, 0, 0, 0, 0, 0, 0, 0, 0},
  {10, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}
};
ControlPanel cp1(cp1l, (sizeof(cp1l) / sizeof(cp1l[0])));



void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  if (DEVMODE)
  {
    Serial.begin(9600); // start serial for output
    Serial.println("Start Master");
  }
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLDOWN);
}


void loop()
{
  fadVal = analogRead(11);
  motorSpeed = map(fadVal, 0, 1024, 0, 255);
  analogWrite(2, motorSpeed);
  fadVal2 = analogRead(10);
  fadVal3 = analogRead(5);
  int touchVal = touchRead(30);
  if (fadVal2 > 900)
  {
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLDOWN);
  }
  else if (fadVal2 < 100)
  {
    pinMode(3, INPUT_PULLDOWN);
    pinMode(4, INPUT_PULLUP);
  }
  /*else{
   pinMode(3, INPUT_PULLDOWN);
   pinMode(4, INPUT_PULLDOWN);fadVal
 }*/
 if(touchVal > 2000){
  Serial.println("touchVal");
  Serial.println(touchVal);
 }
 /* Serial.println("motorSpeed");
  Serial.println(fadVal);
  Serial.println("fadVal2");
  Serial.println(fadVal2);
  Serial.println("fadVal3");
  Serial.println(fadVal3);*/
  /* counter++; */
  // Serial.println(cp1._controlCount);
  // delay(50);
}


void SyncSlaves()
{

}


