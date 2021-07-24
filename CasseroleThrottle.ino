
#include "encoder.h"
#include "display.h"
#include "led.h"
#include "pwmOutput.h"

#define MIN_CMD_STEP 0.05/4.0

#define DEBUG 

boolean isEnabled = false;
boolean btnPrev = false;
double curMotorCmd = 0.0;

long prevEncoderCount = 0;

void setup()
{
    initEncoder();
    initLED();
    initPWMOutput();
    Serial.begin(115200);
}

void loop()
{
    // Read inputs from encoder
    updateEncoder();

    // Read button and update enabled/disabled state
    boolean btnCur = getEncoderButton();
    if(btnCur == true && btnPrev == false){
        isEnabled = !isEnabled;
        if(isEnabled){
            setPWMOutputActive();
        } else {
            setPWMOutputInactive();
        }
    }

    // Read the new encoder position and convert to a change in current speed command
    long curEncCount = getEncoderPosition();
    double motorSpdDelta = (curEncCount - prevEncoderCount)*MIN_CMD_STEP;

    // Calculate current motor command, including range limits.
    if(isEnabled){
        curMotorCmd += motorSpdDelta;

        if(curMotorCmd > 1.0){
            curMotorCmd = 1.0;
        } else if (curMotorCmd < -1.0){
            curMotorCmd = -1.0;
        }
    } else {
        curMotorCmd = 0.0;
    }
    setPWMVal(curMotorCmd);

    // Calculate LED state
    if(isEnabled){
        setLEDActiveOutput(curMotorCmd);
    } else {
        setLEDIdle();
    }

    // Update outputs
    updatePWM();
    updateLED();

    // Save state for next loop
    btnPrev = btnCur;
    prevEncoderCount = curEncCount;

    //debug
    #ifdef DEBUG
    Serial.println("==============================");
    Serial.println(curEncCount);
    Serial.println(btnCur);
    Serial.println(isEnabled);
    Serial.println(curMotorCmd);
    Serial.println("==============================\n\n");
    #endif

}
