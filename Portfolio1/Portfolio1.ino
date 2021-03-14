#include <Servo.h>

Servo servo;

//Define pins
const int servoPin = 9;
const int photoRes1 = 2;
const int photoRes2 = 1;
const int okLedPin = 11;
const int workingLedPin = 12;

//Define constants
const int tolerance = 40; //Needs to be adjusted in production
const int stepSize = 5;
const int maxpos = 30;
const int minpos = 10;

int startPos = minpos;
int lightVal1;
int lightVal2;
int pos;

void setup() {
  Serial.begin(9600);   //Debug
  pinMode(okLedPin, OUTPUT);
  pinMode(workingLedPin, OUTPUT);
  servo.attach(servoPin);  
  servo.write(startPos);
  pos = startPos;
  findBestPosition();
}

void loop() {
  lightVal1 = analogRead(photoRes1);
  lightVal2 = analogRead(photoRes2);
  Serial.print("Light Value 1: ");  //Debug
  Serial.println(lightVal1);            //Debug
  Serial.print("Light Value 2: ");  //Debug
  Serial.println(lightVal2);            //Debug
  
  
   
  int diff = lightVal1 - lightVal2;
  Serial.println("Difference: "); //Debug
  Serial.print(diff);             //Debug
  Serial.println("---------");    //Debug
  
  if (diff < -tolerance && pos < maxpos) {
    digitalWrite(workingLedPin, HIGH);
    digitalWrite(okLedPin, LOW);
    pos = pos+stepSize;
    servo.write(pos);
  } else if (diff > tolerance && pos > minpos) {
    digitalWrite(workingLedPin, HIGH);
    digitalWrite(okLedPin, LOW);
    pos = pos-stepSize;
    servo.write(pos);
  } else {
    digitalWrite(okLedPin, HIGH);
    digitalWrite(workingLedPin, LOW);
  }
  Serial.println("position:");    //Debug
  Serial.println(servo.read());   //Debug
  Serial.println("------------"); //Debug
  delay(500); //Can be longer in production
}

void findBestPosition() {
  int bestPos = startPos;
  int bestLight = 0;

  while(pos < maxpos) {
    lightVal1 = analogRead(photoRes1);
    lightVal2 = analogRead(photoRes2);
    int totalLight = lightVal1 + lightVal2;
    
    if(totalLight > bestLight) {
      bestLight = totalLight;
      bestPos = pos;  
    }

    pos += stepSize;
    servo.write(pos);
    delay(800);
  }
  Serial.println("------------"); //Debug
  Serial.println("Best position: ");    //Debug
  Serial.println(bestPos);   //Debug
  Serial.println("With max light of: "); //Debug
  Serial.println(bestLight); //Debug
  Serial.println("------------"); //Debug
  pos = bestPos;
  servo.write(pos);
  delay(3000);
}
