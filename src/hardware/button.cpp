#include "button.h"

Button::Button(int inputPin, unsigned int pulseWidth) :
  inputPin(inputPin),
  buttonState(digitalRead(inputPin)),
  lastPress(buttonState == HIGH ? millis() : 0),
  pulseWidth(pulseWidth),
  bufferState(false)
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
