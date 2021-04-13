#include "power.h"

PowerController::PowerController(int pin, int pwmResolution) :
  pwmPin(pin),
  dutyLevel(0),
  powerState(PowerState::Off),
  maxDutyLevel((1 << pwmResolution) - 1)
{
  pinMode(pwmPin, OUTPUT);
  PWM_resolution(pwmPin, pwmResolution, CORRECT_PWM);
}

void PowerController::initialize() {
  togglePwm(false);
  togglePowerMode(false);
}

const PowerState PowerController::getPowerState() const {
  return powerState;
}

const int PowerController::getPwmDuty() const {
  return dutyLevel;
}

void PowerController::powerOn() {
  if (powerState == PowerState::On) {
    return;
  }

  if (powerState == PowerState::Pwm) {
    togglePwm(false);
  }

  togglePowerMode(true);
  powerState = PowerState::On;
}

void PowerController::powerOff() {
  if (powerState == PowerState::Off) {
    return;
  }

  if (powerState == PowerState::Pwm) {
    togglePwm(false);
  }

  togglePowerMode(false);
  powerState = PowerState::Off;
}

void PowerController::setPwmDuty(int duty) {
  bool pwmEnabled = powerState == PowerState::Pwm;

  if (pwmEnabled && (duty == dutyLevel)) {
    return;
  }

  if (!pwmEnabled) {
    if (powerState == PowerState::On) {
      togglePowerMode(false);
    }

    togglePwm(true);
    powerState = PowerState::Pwm;
  }

  int newDuty = duty;

  if (newDuty < 0) {
    newDuty = 0;
  } else if (newDuty > maxDutyLevel) {
    newDuty = maxDutyLevel;
  }

  if (newDuty != dutyLevel) {
    dutyLevel = newDuty;
    PWM_set(pwmPin, dutyLevel);
  }
}

void PowerController::changePwmDuty(int changeBy) {
  if (changeBy == 0) {
    return;
  }

  setPwmDuty(dutyLevel + changeBy);
}

void PowerController::togglePowerMode(bool powered) {
  digitalWrite(pwmPin, powered ? HIGH : LOW);
}

void PowerController::togglePwm(bool enabled) {
  if (enabled) {
    PWM_attach(pwmPin);
    return;
  }

  dutyLevel = 0;
  PWM_detach(pwmPin);
}
