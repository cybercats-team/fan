#include "button.h"

Button::Button(int inputPin) :
  inputPin(inputPin),
  bufferState(false)
{
  pinMode(inputPin, INPUT);
  buttonState = digitalRead(inputPin);
}

bool Button::hasPressed() {
  int reading = digitalRead(inputPin);

  if (reading != buttonState) {
    bufferState = (buttonState == HIGH) && (reading == LOW);
    buttonState = reading;
  }

  bool pressed = bufferState;

  if (pressed) {
    bufferState = false;
  }

  return pressed;
};
