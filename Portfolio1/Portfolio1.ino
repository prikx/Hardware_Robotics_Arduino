#include <Servo.h>

Servo servo; // erstellt ein Servo-Objekt um einen Servomotor zu steuern

const int photoRes1 = 2;
const int photoRes2 = 1;
const int tolerance = 50; //Needs to be adjusted in production
const int stepsize = 5;
const int maxpos = 170;
const int minpos = 10;

int startPos = 90;
int lightVal1;
int lightVal2;
int pos;

void setup() {
  Serial.begin(9600);   //Debug
  servo.attach(9);  // verknüpft den Servomotor an Pin 9 mit dem Servo-Objekt
  servo.write(startPos);
  pos = startPos;
}

void loop() {
  
  lightVal1 = analogRead(photoRes1);
  lightVal2 = analogRead(photoRes2);
  
  Serial.println(lightVal1);  //Debug
  Serial.println(lightVal2);  //Debug
  Serial.println("---");  //Debug
  
   
  int diff = lightVal1 - lightVal2;
  Serial.println(diff); //Debug
  Serial.println("---------");  //Debug
  
  if (diff < -tolerance) {
    if (pos < maxpos) {
      pos = pos+5;
    servo.write(pos);
    }
  } else if (diff > tolerance) {
      if (pos > minpos) {
         pos = pos-5;
        servo.write(pos);
      }
  }
  Serial.println("position:");
  Serial.println(servo.read());
  Serial.println("------------");
  delay(500); //Can be longer in production
}
