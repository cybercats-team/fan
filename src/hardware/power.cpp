#include "power.h"

PowerController::PowerController(int pin, int pwmResolution) :
  pwmPin(pin),
  maxDutyLevel((1 << pwmResolution) - 1),
  enabled(false),
  pwmEnabled(false),
  pwmDuty(0)
{
  pinMode(pwmPin, OUTPUT);
  PWM_resolution(pwmPin, pwmResolution, CORRECT_PWM);
  Serial.begin(9600);
}

void PowerController::initialize() {
  togglePwmMode(false);
  togglePowerMode(false);
}

const bool PowerController::isEnabled() const {
  return enabled;
}

const bool PowerController::isPwmEnabled() const {
  return pwmEnabled;
}

const float PowerController::getPwmDuty() const {
  return pwmDuty;
}

void PowerController::powerOn() {
  if (enabled) {
    return;
  }

  enabled = true;
  enablePwm();
}

void PowerController::powerOff() {
  if (!enabled) {
    return;
  }

  disablePwm();
  togglePowerMode(false);
  enabled = false;
}

void PowerController::enablePwm() {
  if (!enabled || pwmEnabled) {
    return;
  }

  togglePwmMode(true);
  pwmEnabled = true;
}

void PowerController::disablePwm() {
  if (!pwmEnabled) {
    return;
  }

  togglePwmMode(false);
  togglePowerMode(true);
  pwmEnabled = false;
}

void PowerController::setPwmDuty(float duty) {
  if (duty == pwmDuty) {
    return;
  }

  pwmDuty = duty;

  if (pwmDuty < 0.0f) {
    pwmDuty = 0.0f;
  } else if (pwmDuty > 100.0f) {
    pwmDuty = 100.0f;
  }

  PWM_set(pwmPin, round(((float) maxDutyLevel) * duty / 100.0f));
}

void PowerController::changePwmDuty(float changeBy) {
  if (changeBy == 0.0f) {
    return;
  }

  setPwmDuty(pwmDuty + changeBy);
}

void PowerController::togglePowerMode(bool powered) {
  digitalWrite(pwmPin, powered ? HIGH : LOW);
}

void PowerController::togglePwmMode(bool enabled) {
  if (enabled) {
    PWM_attach(pwmPin);
    return;
  }

  PWM_detach(pwmPin);
}
