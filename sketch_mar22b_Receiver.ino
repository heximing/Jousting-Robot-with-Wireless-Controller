#include <Servo.h>  // servo library

Servo servoWheelLeft;      // Left wheel servo control object
Servo servoWheelRight;     // Right wheel servo control object
Servo servoLanceLR;        // Left arm servo control object
Servo servoLanceUD;    // Left forearm servo control object
short lanceUD_Position = 90;      // position for Servo arms
short lanceLR_Position = 90;      // position for Servo arms
short myData[] = {0, 0, 0, 0, 0, 33};

void setup() {
  // put your setup code here, to run once:
  servoLanceLR.attach(9);
  servoLanceLR.write(lanceLR_Position);
  servoLanceUD.attach(10);
  servoLanceUD.write(lanceUD_Position);
  servoWheelLeft.attach(11);
  servoWheelLeft.write(90);
  servoWheelRight.attach(12);
  servoWheelRight.write(90);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 6){
    if (Serial.read() == 64){
      for (int i=0;i<5;i++){
        myData[i] = Serial.read();
        // Serial.print(myData[i]); // for debug
        // Serial.print(", "); // for debug
      }
      // Serial.println(""); // for debug

      wheelMove(myData[0], myData[1], myData[2]);

      // Lance movemont from here, UD = 0~180, LR = 0~180
      // Joystick on Controller rotated 90 degree clockwise
      lanceUD_Position = map(myData[3], 1, 123, 0, 180);
      lanceUD_Position = constrain(lanceUD_Position, 0, 180);
      servoLanceUD.write(lanceUD_Position);
      // Serial.print(lanceUD_Position); // for debug
      // Serial.print(", "); // for debug
      lanceLR_Position = map(myData[4], 1, 123, 180, 0);
      lanceLR_Position = constrain(lanceLR_Position, 0, 180);
      servoLanceLR.write(lanceLR_Position);
      // Serial.print(lanceLR_Position); // for debug
      // Serial.print(", "); // for debug
      // Serial.println("\n"); // for debug

    } // end if (Serial.read() == 64)
  } // end if (Serial.available() > 6)
} // end void loop()

void wheelMove(int left, int right, int back){
  // wheelLeft forward = 180
  // wheelRight forward = 0
  if(left > 100 && right > 100){ // forward
    servoWheelLeft.write(180);
    servoWheelRight.write(0);
  }
  else if (left < 20 && right > 100 && back < 20){ // right turn
    servoWheelLeft.write(180);
    servoWheelRight.write(180);
  }
  else if (left > 100 && right < 20 && back < 20){ // left turn
    servoWheelLeft.write(0);
    servoWheelRight.write(0);
  }
  else if (left < 20 && right < 20 && back > 100){ // backward
    servoWheelLeft.write(0);
    servoWheelRight.write(180);
  }
  else if (left > 100 && right < 20 && back > 100){ // backward U-left
    servoWheelLeft.write(90);
    servoWheelRight.write(180);
  }
  else if (left < 20 && right > 100 && back > 100){ // backward U-right
    servoWheelLeft.write(0);
    servoWheelRight.write(90);
  }
  else{
    servoWheelLeft.write(90);
    servoWheelRight.write(90);
  }
} // end int wheelMove(int wheelLR, int wheelUD)
