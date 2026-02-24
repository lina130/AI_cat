#include <Arduino.h>
#include "servo.h"


const int servoPins[] = {21, 14, 16, 4};  
const int servoCount = sizeof(servoPins)/sizeof(servoPins[0]);
const int PWM_PERIOD = 20000; 


void set_servo(int pin, int angle) {
  angle = constrain(angle, 0, 180); 
  int pulse = map(angle, 0, 180, 500, 2500); 
  

  for(int i=0; i<50; i++){
    digitalWrite(pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(pin, LOW);
    delayMicroseconds(PWM_PERIOD - pulse);
  }
  delay(20);
}

void servo_init() {
  
  for(int i=0; i<servoCount; i++){
    pinMode(servoPins[i], OUTPUT);
  }
  Serial.begin(115200);

}

void tail_servo(){
  set_servo(22, 90);
  set_servo(22, 180);
  set_servo(22, 90);
}

void body_servo(){
  set_servo(14, 90);
  set_servo(14, 180);
  set_servo(14, 90);
}

void ears_servo(){
  set_servo(16, 90);
  set_servo(4, 180);
  set_servo(16, 180);
  set_servo(4, 90);
}
