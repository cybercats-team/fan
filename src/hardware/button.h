#ifndef BUTTON
#define BUTTON

#include <Arduino.h>

class Button {
  private:
    int inputPin;
    int buttonState;
    bool bufferState;
  public:
    Button(int inputPin);
    bool hasPressed();
};

#endif
