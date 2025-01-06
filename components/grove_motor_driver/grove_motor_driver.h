#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace grove_motor_driver {

static const char *const TAG = "grove_motor_driver";

// Command bytes for the motor driver
static const uint8_t CMD_SYSTEM_SETUP = 0x21;
static const uint8_t CMD_DISPLAY_ON = 0x81;
static const uint8_t CMD_DIMMING = 0xE0;
static const uint8_t CMD_MOTOR_A_SPEED = 0x82;
static const uint8_t CMD_MOTOR_B_SPEED = 0x84;
static const uint8_t CMD_MOTOR_A_DIRECTION = 0x83;
static const uint8_t CMD_MOTOR_B_DIRECTION = 0x85;

class GroveMotorDriver : public PollingComponent, public i2c::I2CDevice {
 public:
  GroveMotorDriver() : PollingComponent(1000) {}

  void setup() override;
  void loop() override;
  void update() override;

  /// Set the speed and direction of Motor A
  void set_motor_a(int speed);
  /// Set the speed and direction of Motor B
  void set_motor_b(int speed);

  /// Stop Motor A
  void stop_motor_a();
  /// Stop Motor B
  void stop_motor_b();

 protected:
  /// Send a command to the motor driver
  void send_command_(uint8_t command, uint8_t value);

  int last_motor_a_speed_{0};
  int last_motor_b_speed_{0};
};

}  // namespace grove_motor_driver
}  // namespace esphome
