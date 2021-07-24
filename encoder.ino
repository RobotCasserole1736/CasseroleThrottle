#define encoder0PinA  2
#define encoder0PinB  7
#define encoderButtonPin 16

//Volatile required because this is updated in ISR's
volatile int encoder0Pos = 0;

//Button debouncing
#define MAX_BTN_DBNC 100
boolean buttonDebounced = false;
int debounceCount = MAX_BTN_DBNC;

void initEncoder(){
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  pinMode(encoderButtonPin, INPUT_PULLUP);

  // encoder pin on interrupt 
  attachInterrupt(digitalPinToInterrupt(encoder0PinA), doEncoderA, CHANGE);

  // encoder pin on interrupt
  attachInterrupt(digitalPinToInterrupt(encoder0PinA), doEncoderB, CHANGE);
}

boolean getEncoderButton(){
  return buttonDebounced;
}

void updateEncoder(){

  //Read encoder button pin and debounce it.
  //Signal is Active Low
  if(!digitalRead(encoderButtonPin)){
    if(debounceCount > 0){
      debounceCount--;
    }
  } else {
    debounceCount = MAX_BTN_DBNC;
  }

  buttonDebounced = (debounceCount == 0);

}

int getEncoderPosition(){
    return encoder0Pos;
}

void doEncoderA() {
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

void doEncoderB() {
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}
