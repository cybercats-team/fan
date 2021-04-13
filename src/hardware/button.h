#ifndef BUTTON
#define BUTTON

#include <Arduino.h>

class Button {
  private:
    int inputPin;
    int buttonState;
    unsigned long lastPress;
    unsigned int pulseWidth;
    bool bufferState;
  public:
    Button(int inputPin, unsigned int pulseWidth);
    bool hasPressed();
};

#endif
