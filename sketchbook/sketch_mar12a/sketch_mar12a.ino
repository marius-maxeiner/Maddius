void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); // start serial for output
}

void loop() {
  // put your main code here, to run repeatedly:
  short f1 = analogRead(A0);
  Serial.println(f1);
}
