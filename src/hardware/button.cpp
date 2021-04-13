#include "button.h"

Button::Button(int inputPin, unsigned int pulseWidth) :
  inputPin(inputPin),
  bufferState(false),
  lastPress(0),
  buttonState(LOW),
  pulseWidth(pulseWidth)
{
  pinMode(inputPin, INPUT);
}

bool Button::hasPressed() {
  int reading = digitalRead(inputPin);

  if (reading != buttonState) {
    if ((reading == HIGH) && (lastPress == 0)) {
      lastPress = millis();
    }

    if (reading == LOW) {
      if ((millis() - lastPress) >= pulseWidth) {
        bufferState = true;
      }

      lastPress = 0;
    }

    buttonState = reading;
  }

  bool pressed = bufferState;

  if (pressed) {
    bufferState = false;
  }

  return pressed;
}
