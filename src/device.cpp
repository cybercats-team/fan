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
  powerDownBtn(FAN_POWER_DOWN_PIN),
  powerUpBtn(FAN_POWER_UP_PIN),
  powerCtrl(FAN_POWER_PIN, FAN_POWER_RESOLUTION),
  minPowerLevel(FAN_POWER_MIN),
  maxPowerLevel(FAN_POWER_MAX),
  powerLevelScale(FAN_POWER_SCALE)
{
  powerCtrl.initialize();
}

void Device::onLoop() {
  bool powered = powerCtrl.isEnabled();
  float powerLevel = powerCtrl.getPwmDuty();

  if (powerUpBtn.hasPressed()) {
    if (!powered) {
      powerCtrl.powerOn();
      powerCtrl.setPwmDuty(minPowerLevel);
      return;
    }

    if (powerLevel >= maxPowerLevel) {
      powerCtrl.disablePwm();
      return;
    }

    powerCtrl.changePwmDuty(powerLevelScale);
    return;
  }

  if (!powered || !powerDownBtn.hasPressed()) {
    return;
  }

  if (powerLevel <= 0) {
    powerCtrl.powerOff();
    return;
  }

  if (!powerCtrl.isPwmEnabled()) {
    powerCtrl.enablePwm();
    powerCtrl.setPwmDuty(maxPowerLevel);
    return;
  }

  powerCtrl.changePwmDuty(-powerLevelScale);
}
