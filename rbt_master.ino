//this is master

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);

#define finger1Pin 0
#define finger2Pin 1
#define finger3Pin 2
#define finger4Pin 3
#define finger5Pin 4

#define button 8
int buttonstate = 1;

int val = 0;
int fingerNum[] = {170,170,170,20,20};   // robot hand in idle state
byte startPkg = B11111111;
boolean countUp[]= {true,true,true,true,true};

void demo() {
   BTSerial.write(startPkg);
   for (int i=0; i<5; i++){
      if (fingerNum[i] >= 170 && countUp[i])
        if (fingerNum[i] >= 20) { 
          fingerNum[i] -= 10;
          countUp[i] = false;
        }
        else
          fingerNum[i] += 10;
      else {
        if (countUp[i])
          fingerNum[i] += 10;
        else
          if (fingerNum[i] >= 20)
            fingerNum[i] -= 10;
        else {
          fingerNum[i] += 10;
          countUp[i] = true;
        }
      }  
      BTSerial.write(fingerNum[i]);
      delay(10);
      Serial.print(fingerNum[i]);
      if (i!=4)
        Serial.print(", ");
      else
        Serial.println("");
  }
  delay(500);   // delay 500ms to allow the transmission    
}

void control() {
  val = analogRead(finger1Pin);   // Finger 1 reading (tight=small, relax=large)
  fingerNum[0] = map(val,300,450,20,170);
  fingerNum[0] = min(fingerNum[0],170);
  fingerNum[0] = max(fingerNum[0],20);
  Serial.print(fingerNum[0]);
  Serial.print(", ");
  val = analogRead(finger2Pin);   // Finger 2 reading (tight=small, relax=large)
  fingerNum[1] = map(val,300,450,20,170);
  fingerNum[1] = min(fingerNum[1],170);
  fingerNum[1] = max(fingerNum[1],20);
  Serial.print(fingerNum[1]);
  Serial.print(", ");
  val = analogRead(finger3Pin);   // Finger 3 reading (tight=small, relax=large)
  fingerNum[2] = map(val,300,450,20,170);
  fingerNum[2] = min(fingerNum[2],170);
  fingerNum[2] = max(fingerNum[2],20);
  Serial.print(fingerNum[2]);
  Serial.print(", ");
  val = analogRead(finger4Pin);   // Finger 4 reading (tight=large, relax=small)
  fingerNum[3] = map(val,250,420,170,20);
  fingerNum[3] = min(fingerNum[3],170);
  fingerNum[3] = max(fingerNum[3],20);
  Serial.print(fingerNum[3]);
  Serial.print(", ");
  val = analogRead(finger5Pin);   // Finger 5 reading (tight=large, relax=small)
  fingerNum[4] = map(val,250,420,170,20);
  fingerNum[4] = min(fingerNum[4],170);
  fingerNum[4] = max(fingerNum[4],20);
  Serial.print(fingerNum[4]);
  Serial.println("");
  BTSerial.write(startPkg);
  for (int i=0; i<5; i++){
     BTSerial.write(fingerNum[i]);
     delay(10);
  }
  delay(500);  // delay 500ms to allow the transmission 
}

void setup(){
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  BTSerial.begin(38400);
}

void loop(){
  buttonstate = digitalRead(button);
  if (buttonstate == LOW)
    control();
  else
    demo();
  delay(300);    // delay 300ms for another reading
}
