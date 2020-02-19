//this is slave

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);      // Rx, Tx cross-over for data communication

#include <Servo.h>

Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
Servo servo3;  // create servo object to control a servo
Servo servo4;  // create servo object to control a servo
Servo servo5;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int finger[]= {170,170,170,20,20};          // idle position

#define button 8
int buttonstate = 1;
#define startPkg B11111111
byte start = B00000000;

void servoMove() {
  servo1.write(finger[0]);
  delay(20);   
  servo2.write(finger[1]);
  delay(20);   
  servo3.write(finger[2]);
  delay(20);       
  servo4.write(finger[3]);
  delay(20);           
  servo5.write(finger[4]);            
  delay(20);
}

void test(){
  finger[0] = 170;    // idle position
  finger[1] = 170;
  finger[2] = 170;
  finger[3] = 20;
  finger[4] = 20;
  servoMove();
  delay(500);
  Serial.println("idle");
  finger[0] = 20;    // close position
  finger[1] = 20;
  finger[2] = 20;
  finger[3] = 170;
  finger[4] = 170;
  servoMove();
  delay(500);
  Serial.println("close");
  finger[0] = 170;    // 1 finger relax position
  finger[1] = 20;
  finger[2] = 20;
  finger[3] = 170;
  finger[4] = 170;
  servoMove();
  delay(500);  
  Serial.println("Finger 1 relax");
  finger[0] = 170;    // 1 finger relax position
  finger[1] = 170;    // 2 finger relax position
  finger[2] = 20;
  finger[3] = 170;
  finger[4] = 170;
  servoMove();
  delay(500);
  Serial.println("Finger 2 relax");
  finger[0] = 170;    // 1 finger relax position
  finger[1] = 170;    // 2 finger relax position
  finger[2] = 170;    // 3 finger relax position
  finger[3] = 170;
  finger[4] = 170;
  servoMove();
  delay(500);
  Serial.println("Finger 3 relax");
  finger[0] = 170;    // 1 finger relax position
  finger[1] = 170;    // 2 finger relax position
  finger[2] = 170;    // 3 finger relax position
  finger[3] = 20;     // 4 finger relax position
  finger[4] = 170;
  servoMove();
  delay(500);
  Serial.println("Finger 4 relax");
  finger[0] = 170;    // idle position
  finger[1] = 170;    
  finger[2] = 170;    
  finger[3] = 20;     
  finger[4] = 20;
  servoMove();
  delay(500);
  Serial.println("idle");
  finger[0] = 170;    
  finger[1] = 170;    
  finger[2] = 170;
  finger[3] = 20;
  finger[4] = 170;    // 5 finger tight position
  servoMove();
  delay(500);
  Serial.println("Finger 5 tighten");
  finger[0] = 170;    
  finger[1] = 170;    
  finger[2] = 170;    
  finger[3] = 170;  // 4 finger tight position
  finger[4] = 170;  // 5 finger tight position
  servoMove();
  delay(500);
  Serial.println("Finger 4 tighten");
  finger[0] = 170;  
  finger[1] = 170;   
  finger[2] = 20;   // 3 finger tight position
  finger[3] = 170;  // 4 finger tight position
  finger[4] = 170;  // 5 finger tight position
  servoMove();
  delay(500);
  Serial.println("Finger 3 tighten");
  finger[0] = 170;  
  finger[1] = 20;   // 2 finger tight position
  finger[2] = 20;   // 3 finger tight position
  finger[3] = 170;  // 4 finger tight position
  finger[4] = 170;  // 5 finger tight position
  servoMove();
  delay(500);
  Serial.println("Finger 2 tighten");
  finger[0] = 20;    // close position
  finger[1] = 20;
  finger[2] = 20;
  finger[3] = 170;
  finger[4] = 170;
  servoMove();
  delay(500);
  Serial.println("close");
  finger[0] = 20;    // OK position
  finger[1] = 170;    
  finger[2] = 170;    
  finger[3] = 170;     
  finger[4] = 170;
  servoMove();
  delay(500);
  Serial.println("OK");
  finger[0] = 170;    // idle position
  finger[1] = 170;    
  finger[2] = 170;    
  finger[3] = 20;     
  finger[4] = 20;
  servoMove();
  delay(500);
  Serial.println("idle");
}

void setup() {
  Serial.begin(9600);
  servo1.attach(3);  // attaches the servo on pin 3 to the servo object
  servo2.attach(4);  // attaches the servo on pin 4 to the servo object
  servo3.attach(5);  // attaches the servo on pin 5 to the servo object
  servo4.attach(6);  // attaches the servo on pin 6 to the servo object
  servo5.attach(7);  // attaches the servo on pin 7 to the servo object
  test();
  pinMode(button, INPUT_PULLUP);
  BTSerial.begin(38400);
}

int i=0;

void loop() {
  if (BTSerial.available() > 0){
    start = BTSerial.read();
    while (start != startPkg) {  
      Serial.print(start);
      finger[i] = start;
      start = BTSerial.read();
      i += 1;
      if (i==5){
        Serial.println("");
        i = 0;
        servoMove();
        break;
      }
      else
        Serial.print(", ");
    }
  }
  // Press test button to re-run testing routine
  delay(100);
  buttonstate = digitalRead(button);
  if (buttonstate == LOW)
    test();
}
