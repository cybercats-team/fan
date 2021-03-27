#ifndef POWER_CONTROLLER
#define POWER_CONTROLLER

#include <Arduino.h>

#include "../lib/GyverPWM.h"

class PowerController {
  private:
    int pwmPin;
    int maxDutyLevel;

    bool enabled;
    bool pwmEnabled;
    float pwmDuty;

    void togglePowerMode(bool enabled);
    void togglePwmMode(bool powered);

  public:
    PowerController(int pin, int pwmResolution);

    void initialize();

    void powerOn();
    void powerOff();
    void enablePwm();
    void disablePwm();
    void setPwmDuty(float duty);
    void changePwmDuty(float changeBy);

    const bool isEnabled() const;
    const bool isPwmEnabled() const;
    const float getPwmDuty() const;
};

#endif