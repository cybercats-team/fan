#include "device.h"

Device * Device::instance;

void Device::setup() {
  if (instance != nullptr) {
    return;
  }

  instance = new Device();
}

void Device::loop() {
  if (instance == nullptr) {
    return;
  }

  instance->onLoop();
}

Device::Device() :
  powerDownBtn(FAN_POWER_DOWN_PIN, FAN_POWER_BTN_PULSE_WIDTH),
  powerUpBtn(FAN_POWER_UP_PIN, FAN_POWER_BTN_PULSE_WIDTH),
  powerCtrl(FAN_POWER_PIN, FAN_POWER_RESOLUTION),
  minPowerLevel(powerCtrl.calculateLevel(FAN_POWER_MIN)),
  maxPowerLevel(powerCtrl.calculateLevel(FAN_POWER_MAX)),
  powerLevelScale(powerCtrl.calculateLevel(FAN_POWER_SCALE))
{
  powerCtrl.initialize();
}

void Device::onLoop() {
  const PowerState powerState = powerCtrl.getPowerState();
  int powerLevel = powerCtrl.getPwmDuty();

  if (powerUpBtn.hasPressed()) {
    onPowerUpPressed();
  }

  if (powerDownBtn.hasPressed()) {
    onPowerDownPressed();
  }
}

void Device::onPowerUpPressed() {
  const PowerState powerState = powerCtrl.getPowerState();
  int powerLevel = powerCtrl.getPwmDuty();

  if (powerState != PowerState::Pwm) {
    if (powerState == PowerState::Off) {
      powerCtrl.setPwmDuty(minPowerLevel);
    }

    return;
  }

  if (powerLevel >= maxPowerLevel) {
    powerCtrl.powerOn();
    return;
  }

  powerCtrl.changePwmDuty(powerLevelScale);
}

void Device::onPowerDownPressed() {
  const PowerState powerState = powerCtrl.getPowerState();
  int powerLevel = powerCtrl.getPwmDuty();

  if (powerState != PowerState::Pwm) {
    if (powerState == PowerState::On) {
      powerCtrl.setPwmDuty(maxPowerLevel);
    }

    return;
  }

  if (powerLevel <= minPowerLevel) {
    powerCtrl.powerOff();
    return;
  }

  powerCtrl.changePwmDuty(-powerLevelScale);
}
