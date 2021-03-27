#ifndef DEVICE
#define DEVICE

#include <Arduino.h>
#include "device_setup.h"

#include "hardware/button.h"
#include "hardware/power.h"

class Device {
  private:
    static Device * instance;
    Button powerDownBtn;
    Button powerUpBtn;
    PowerController powerCtrl;

    float minPowerLevel;
    float maxPowerLevel;
    float powerLevelScale;

    Device();
    void onLoop();
  public:
    static void setup();
    static void loop();
};

#endif
