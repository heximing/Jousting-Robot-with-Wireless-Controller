const int PinWheelLeft = 4;     // the number of the joystick pin
const int PinWheelRight = 5;     // the number of the joystick pin
const int PinWheelBack = 6;     // the number of the joystick pin
const int PinLanceLR = 2;     // the number of the joystick pin
const int PinLanceUD = 3;     // the number of the joystick pin

void setup() {
  // put your setup code here, to run once:
  pinMode(PinWheelLeft, INPUT);
  pinMode(PinWheelRight, INPUT);
  pinMode(PinWheelBack, INPUT);
  pinMode(PinLanceLR, INPUT);
  pinMode(PinLanceUD, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  short myData[] = {0, 0, 0, 0, 0, 0};
  myData[1] = digitalRead(PinWheelLeft);
  myData[2] = digitalRead(PinWheelRight);
  myData[3] = digitalRead(PinWheelBack);
  myData[4] = analogRead(PinLanceLR);
  myData[5] = analogRead(PinLanceUD);
  char myChar[] = {'@', 'A', 'A', 'A', 'A', 'A'};
  myChar[1] = map(myData[1], 0, 1, 0, 126);
  myChar[2] = map(myData[2], 0, 1, 0, 126);
  myChar[3] = map(myData[3], 0, 1, 0, 126);
  myChar[4] = map(myData[4], 0, 1023, 0, 126);
  myChar[5] = map(myData[5], 0, 1023, 0, 126);
  /*
   * 
   for (byte i = 0;i < 6; i++){
    Serial.print(myData[i]);
    Serial.print(", ");
  }
  Serial.println("");
  */
  for (byte i = 0;i < 6; i++){
    Serial.print(myChar[i]);
    //Serial.print(", ");
  }
  Serial.println("");
  delay(200);
}
