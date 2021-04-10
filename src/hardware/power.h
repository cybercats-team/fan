#ifndef POWER_CONTROLLER
#define POWER_CONTROLLER

#include <Arduino.h>

#include "../lib/GyverPWM.h"

enum class PowerState {
  Off,
  On,
  Pwm
};

class PowerController {
  private:
    int pwmPin;
    int maxDutyLevel;
    int dutyLevel;
    PowerState powerState;

    void togglePowerMode(bool onOff);
    void togglePwm(bool enabled);
  public:
    PowerController(int pin, int pwmResolution);

    void initialize();

    void powerOn();
    void powerOff();
    void setPwmDuty(int duty);
    void changePwmDuty(int changeBy);

    const PowerState getPowerState() const;
    const int getPwmDuty() const;

    inline int calculateLevel(int percents) {
      return round(((float) maxDutyLevel) * ((float) percents) / 100.0f);
    }
};

#endif