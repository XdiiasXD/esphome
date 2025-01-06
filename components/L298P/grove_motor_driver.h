#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace grove_motor_driver {

class GroveMotorDriver : public PollingComponent, public i2c::I2CDevice {
 public:
  /// Set the polling interval for updates (not necessary here, but can be useful for state monitoring)
  GroveMotorDriver() : PollingComponent(1000) {}

  void setup() override;
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
  /// I2C Commands for Motor A and B
  static constexpr uint8_t CMD_MOTOR_A_SPEED = 0x82;
  static constexpr uint8_t CMD_MOTOR_B_SPEED = 0x84;
  static constexpr uint8_t CMD_MOTOR_A_DIRECTION = 0x83;
  static constexpr uint8_t CMD_MOTOR_B_DIRECTION = 0x85;
};

}  // namespace grove_motor_driver
}  // namespace esphome
