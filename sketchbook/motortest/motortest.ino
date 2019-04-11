     byte _motorUpIOPin = 3;
   byte _motorDownIOPin = 4;
   byte _motorSpeedPWM = 5;
   // byte _analogPin = 1;
   byte _motorOn = 2;


void setup() {
  // put your setup code here, to run once:
  // Motor Test
  pinMode(_motorUpIOPin, OUTPUT);
  pinMode(_motorDownIOPin, OUTPUT);
  pinMode(_motorOn, OUTPUT);
  Serial.begin(57600); // start serial for output
}

void loop() {
  
  // analogRead(_analogPin);
  analogWrite(_motorSpeedPWM , 100);
  // put your main code here, to run repeatedly:
  delay(1000);
  digitalWrite(_motorOn, HIGH);
  digitalWrite(_motorUpIOPin, HIGH);
  digitalWrite(_motorDownIOPin, LOW);
  delay(10);
  digitalWrite(_motorUpIOPin, LOW);
  digitalWrite(_motorDownIOPin, HIGH);
  delay(10);
  digitalWrite(_motorUpIOPin, LOW);
  digitalWrite(_motorDownIOPin, LOW);
  digitalWrite(_motorOn, LOW);
  delay(1000);

}
