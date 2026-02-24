#ifndef SERVO_CONTROL_H 
#define SERVO_CONTROL_H

#include <Arduino.h>  


extern const int servoPins[];        
extern const int servoCount;         
extern const int PWM_PERIOD;         

void set_servo(int pin, int angle);
void servo_init();
void tail_servo();
void body_servo();
void ears_servo();

#endif  
