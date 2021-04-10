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

    int minPowerLevel;
    int maxPowerLevel;
    int powerLevelScale;

    Device();
    void onLoop();
    void onPowerUpPressed();
    void onPowerDownPressed();
  public:
    static void setup();
    static void loop();
};

#endif
