
#define LED_RED_PIN 5
#define LED_GRN_PIN 6
#define LED_BLU_PIN 3

boolean isActiveLED;
double outValLED;

void initLED(){
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GRN_PIN, OUTPUT);
  pinMode(LED_BLU_PIN, OUTPUT);
}

void setLEDActiveOutput(double value){
    outValLED = value;
    isActiveLED = true;
}

void setLEDIdle(){
    isActiveLED = false;
}

void updateLED(){

    unsigned long curTime = millis();

    if(isActiveLED){

        double pulseFreq = max(0.2, abs(outValLED*6));
        
        int ledBrightness = 0;

        if(abs(outValLED) > 0.95){
            // Full power = solid
            ledBrightness = 255;
        } else {
            // Intermedeate power = blinky
            ledBrightness = 255*abs(sin(curTime/1000.0*2*3.14159*pulseFreq));
        }

        if(outValLED > 0.05){
            //Forward is green
            analogWrite(LED_RED_PIN, 0);
            analogWrite(LED_GRN_PIN, ledBrightness*0.5); //dang nab green is bright
        } else if (outValLED < -0.05){
            //Reverse is red
            analogWrite(LED_RED_PIN, ledBrightness);
            analogWrite(LED_GRN_PIN, 0);
        } else {
            // Stopped is yellow
            analogWrite(LED_RED_PIN, 255);
            analogWrite(LED_GRN_PIN, 20);
        }

        analogWrite(LED_BLU_PIN, 0);

    } else {
        int idlePulseVal = 255*abs(sin(curTime/1000.0*2*3.14159*0.25));
        Serial.print(idlePulseVal);
        //Pulsey blue for idle
        analogWrite(LED_RED_PIN, 0);
        analogWrite(LED_GRN_PIN, 0);
        analogWrite(LED_BLU_PIN, idlePulseVal);
    }
}
