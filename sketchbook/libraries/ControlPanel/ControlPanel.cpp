#include "Arduino.h"
#include "ControlPanel.h"

MotorA::MotorA(byte motorUpIOPin, byte motorDownIOPin, byte motorSpeedPWM){
    _motorUpIOPin = motorUpIOPin;
    _motorDownIOPin = motorDownIOPin;
    _motorSpeedPWM = motorSpeedPWM;
    _speed = 0;
    pinMode(_motorUpIOPin, OUTPUT);
    pinMode(_motorDownIOPin, OUTPUT);
}

void MotorA::setSpeed(byte speed)
{
    _speed = speed;
    analogWrite(_motorSpeedPWM , speed);
}

void MotorA::motorUp()
{
    digitalWrite(_motorUpIOPin, HIGH);
    digitalWrite(_motorDownIOPin, LOW);
}

void MotorA::motorDown()
{
    digitalWrite(_motorUpIOPin, LOW);
    digitalWrite(_motorDownIOPin, HIGH);
}

void MotorA::motorStop()
{
    setSpeed(0);
    digitalWrite(_motorUpIOPin, LOW);
    digitalWrite(_motorDownIOPin, LOW);
}

MotorB::MotorB(byte motorUpIOPin, byte motorDownIOPin, byte motorSpeedPWM, byte motorStandby){
    _motorUpIOPin = motorUpIOPin;
    _motorDownIOPin = motorDownIOPin;
    _motorSpeedPWM = motorSpeedPWM;
    _motorStandby = motorStandby;
    _speed = 0;
    pinMode(_motorStandby, OUTPUT);
    pinMode(_motorUpIOPin, OUTPUT);
    pinMode(_motorDownIOPin, OUTPUT);
}

void MotorB::setSpeed(byte speed)
{
    // Serial.print("Motor setSpeed:");
    // Serial.println(speed);
    _speed = speed;
    analogWrite(_motorSpeedPWM , speed);
}

void MotorB::motorUp()
{
    // Serial.println("Motor motorUp");
    digitalWrite(_motorStandby, HIGH);
    digitalWrite(_motorUpIOPin, HIGH);
    digitalWrite(_motorDownIOPin, LOW);
}

void MotorB::motorDown()
{
    // Serial.println("Motor motorDown");
    digitalWrite(_motorStandby, HIGH);
    digitalWrite(_motorUpIOPin, LOW);
    digitalWrite(_motorDownIOPin, HIGH);
}

void MotorB::motorStop()
{
    // setSpeed(0);
    // digitalWrite(_motorStandby, LOW);
    digitalWrite(_motorUpIOPin, LOW);
    digitalWrite(_motorDownIOPin, LOW);
}


MotorPWM::MotorPWM(byte motorUpPWM, byte motorDownPWM){
    _motorUpPWM = motorUpPWM;
    _motorDownPWM = motorDownPWM;
    _speed = 0;
}

void MotorPWM::setSpeed(byte speed)
{
    _speed = speed;
}

void MotorPWM::motorUp()
{
    analogWrite(_motorUpPWM , _speed);
    analogWrite(_motorDownPWM , 0);
}

void MotorPWM::motorDown()
{
    analogWrite(_motorUpPWM , 0);
    analogWrite(_motorDownPWM , _speed);
}

void MotorPWM::motorStop()
{
    analogWrite(_motorUpPWM , 0);
    analogWrite(_motorDownPWM , 0);
}


Fader::Fader(byte analogPin, byte touchPin, Motor *motor)//   byte motorUpPin, byte motorDownPin 
{
    _analogPin = analogPin;
    _touchPin = touchPin;
    _motor = motor;
    _valueTarget = 0;
    // _lastValues = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    _lastValueCount = 0;
    _startTouch = readTouch();
    _motor->setSpeed(160);
   /* delay(2000);
    Serial.println("Nstarrt");
    _motor->setSpeed(200);
 

    delay(2000);
    _motor->setSpeed(200);
    Serial.println("down");
    _motor->motorDown();
    delay(2000);
    Serial.println("stop");
    _motor->motorStop();
    delay(2000);
    _motor->setSpeed(200);
    Serial.println("up");
    _motor->motorUp();
    delay(2000);
    Serial.println("stop");
    _motor->motorStop();
    delay(60000);*/
}

short Fader::readAnalog()
{
    return analogRead(_analogPin);
}

short Fader::readTouch()
{
    //#if CHIPSET == ARDUINO_NANO
      //  return 0;
    ///#else 
        return touchRead(_touchPin);
    //#endif
}

short Fader::update()
{
    int touchValue = readTouch();
    _touched = touchValue > _startTouch + 300;
    int newValue = 0;
    // int newMid = 0;
    int sum = 0;
    _lastValues[_lastValueCount] = readAnalog();
    for (int i = 0; i < LASTVALARRLEN; i++){
        sum = sum + _lastValues[i];
    }
    _lastValueCount++;
    if(_lastValueCount == LASTVALARRLEN){
        _lastValueCount = 0;
    }

    newValue = (sum / LASTVALARRLEN); // + _lastMid) / 2;
    if (newValue < TOLERANZ) {
        newValue = 0;
    }else if (newValue > 1023 - TOLERANZ) {
        newValue = 1023;
    }else if (
            newValue <= _lastMid + TOLERANZ
            && newValue >= _lastMid - TOLERANZ){
        newValue = _lastMid;
    }else if (_touched) {

    }
    // Human Changed
    if(_lastMid != newValue && _touched){
        _humanChanged = true;
        _valueTarget = newValue;
        Serial.println("Human");
        Serial.println(touchValue);
    } else {
        _humanChanged = false;
    }

    // MOTOR
    if(!_humanChanged){
        
    }
    if ((_valueTarget <= newValue + 50
        && _valueTarget >= newValue - 50) || _humanChanged){
        _motor->motorStop();
        // Serial.println("Motor Stop");
    }else if (!_humanChanged){
        int distance = abs(_valueTarget - newValue);
        // byte speed = 0;
        // map(distance, 0, 1023, 130, 255);
        // Serial.println(speed);
        // _motor->setSpeed(speed);
        /*if(distance > 300){
            speed = 230;
        }else if(distance > 160){
            speed = 200;
        }else if(distance > 120){
            speed = 180;
        }else if(distance > 60){
            speed = 140;
        }else if(distance > 10){
            //speed = 255;
            speed = 128;
        }else {
            speed = 0;
        }*/

        // _motor->setSpeed(speed);
        if (newValue > _valueTarget) {
            //_motor->setSpeed(180);
            _motor->motorDown();
        } else {
            //_motor->setSpeed(180);
            _motor->motorUp();
        }

        /*Serial.print("New:");
        Serial.println(newValue);
        Serial.print("Target:");
        Serial.println(_valueTarget);
        Serial.print("Distance:");
        Serial.println(distance);
        Serial.print("Speed:");
        Serial.println(speed);*/
    }
    // Erst nach X Zyklen Ändern ??
    _lastMid = newValue;
    _updateCount++;
    return newValue;
}
