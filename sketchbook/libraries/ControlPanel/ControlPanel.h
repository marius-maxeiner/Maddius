#ifndef ControlPanel_h
#define ControlPanel_h

#include "Arduino.h"
 
#define LASTVALARRLEN 24
#define TOLERANZ 6

class Control{
  public:
    Control();
    void update();
};

class Button {
  public:
  byte _buttonIO;
  bool _humanChanged;
  bool _lastValue;
  bool _value;
  Button(byte buttonIO){
    _buttonIO = buttonIO;
    pinMode(_buttonIO, INPUT_PULLUP);
  };

  bool update(){
    _lastValue = _value;
    int value = digitalRead(_buttonIO);
    if (value == LOW){
      _value = true;
    } else {
      _value = false;
    }
    if(_lastValue != _value){
      _humanChanged = true;
    } else {
      _humanChanged = false;
    }
    return _value;
  };
};

/*
* Mouse Like Joystik
*
*/
class JoyStick {
  public:
  int range = 12;               // output range of X or Y movement
  int responseDelay = 5;        // response delay of the mouse, in ms
  int _threshold = range / 4;    // resting threshold
  int center = range / 2;       // resting position value
  bool _humanChanged;
  int _xValue;
  int _yValue;
  byte _xAnalog;
  byte _yAnalog;
  JoyStick(byte xAnalog, byte yAnalog){
    _xAnalog = xAnalog;
    _yAnalog = yAnalog;
    _xValue = 0;
    _yValue = 0;
  };

  void update(){
    int _lastXValue = _xValue;
    int _lastYValue = _yValue;
    int movex = readAxis(_xAnalog);
    int movey = readAxis(_yAnalog);
    _xValue = _xValue + movex;
    _yValue = _yValue + movey;

    if(_xValue > 1023){
      _xValue = 1023;
    } else if (_xValue < 0) {
      _xValue = 0;
    }

    if(_yValue > 1023){
      _yValue = 1023;
    } else if (_yValue < 0) {
      _yValue = 0;
    }

    if(_lastXValue != _xValue 
      || _lastYValue != _yValue){
      _humanChanged = true;
    } else {
      _humanChanged = false;
    }
  };

  int readAxis(int thisAxis) {
    // read the analog input:
    int reading = analogRead(thisAxis);

    // map the reading from the analog input range to the output range:
    reading = map(reading, 0, 1023, 0, range);
    // if the output reading is outside from the rest position threshold, use it:
    int distance = reading - center;
    if (abs(distance) < _threshold) {
      distance = 0;
    }
    // return the distance for this axis:
    return distance;
  }

};

class Motor {
  public:
  Motor(){};
  virtual void setSpeed(byte speed)  {};
  virtual void motorUp() {Serial.println("Motor motorUp");};
  virtual void motorDown() {};
  virtual void motorStop() {};
};

class MotorA : public Motor{
  private:
  public:
  byte _motorUpIOPin;
  byte _motorDownIOPin;
  byte _motorSpeedPWM;
  byte _speed;
  
  MotorA(byte motorUpIOPin, byte motorDownIOPin, byte motorSpeedPWM);
  void setSpeed(byte speed);
  void motorUp();
  void motorDown();
  void motorStop();
};

class MotorB : public Motor{
  private:
  public:
  byte _motorUpIOPin;
  byte _motorDownIOPin;
  byte _motorSpeedPWM;
  byte _motorStandby;
  byte _speed;
  
  MotorB(byte motorUpIOPin, byte motorDownIOPin, byte motorSpeedPWM, byte motorStandby);
  void setSpeed(byte speed);
  void motorUp();
  void motorDown();
  void motorStop();
};

class MotorPWM : public Motor {
  public:
  byte _motorUpPWM;
  byte _motorDownPWM;
  byte _speed;
  MotorPWM(byte motorUpPWM, byte motorDownPWM);
  void setSpeed(byte speed);
  void motorUp();
  void motorDown();
  void motorStop();
};

class Fader{
  public:
  short _lastValueCount;
  short _lastValues[LASTVALARRLEN];
  short _lastMid;
  short _newMid;
  short _faderSpeed;
  Motor* _motor;
  short _valueTarget;
  bool _touched;
  bool _humanChanged;
  short _startTouch;
  Fader(byte analogPin, byte touchPin, Motor *motor); // , Motor* motor
  short readAnalog();
  short readTouch();
  short update();
  short _updateCount;
  byte _analogPin;
  byte _touchPin;
};

/*
* Idea for a centalised logic layer for 
* the out and incoming signals 
*
*/
class ControlPanel
{
  public:
    ControlPanel(Control control[], byte controlCount);
    // void syncControls();
    Control* _control[64];
};


#endif