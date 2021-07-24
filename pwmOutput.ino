
#define PWM_OUT_PIN 9

#define PULSE_MIN_US 1000
#define PULSE_MAX_US 2000

#include <Servo.h>

Servo output;

boolean isActive = false;
double outVal = 90;

void initPWMOutput(){
    setPWMOutputInactive();
    pinMode(PWM_OUT_PIN, OUTPUT);
    digitalWrite(PWM_OUT_PIN, false);
}

void setPWMVal(double value){
    outVal = 90 * value + 90;
}

void setPWMOutputActive(){
    output.attach(PWM_OUT_PIN, PULSE_MIN_US, PULSE_MAX_US);
    isActive = true;
}

void setPWMOutputInactive(){
    output.detach();
    isActive = false;
}

void updatePWM(){
    if(isActive){
        output.write(outVal);
    } else {
        output.write(90);
    }

}
