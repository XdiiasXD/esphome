#include "grove_motor_driver.h"
#include "esphome/core/log.h"

namespace esphome {
namespace grove_motor_driver {

static const char *const TAG = "grove_motor_driver";

void GroveMotorDriver::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Grove I2C Motor Driver...");
  this->stop_motor_a();
  this->stop_motor_b();
}

void GroveMotorDriver::update() {
  // Optional: Use this for periodic tasks or to monitor motor state
  ESP_LOGD(TAG, "Grove Motor Driver update called.");
}

void GroveMotorDriver::set_motor_a(int speed) {
  uint8_t direction = (speed >= 0) ? 0x01 : 0x02;  // 0x01 = forward, 0x02 = reverse
  speed = abs(speed);                              // Ensure positive speed
  speed = map(speed, 0, 100, 0, 255);              // Scale speed to 0-255
  this->send_command_(CMD_MOTOR_A_SPEED, speed);
  this->send_command_(CMD_MOTOR_A_DIRECTION, direction);
}

void GroveMotorDriver::set_motor_b(int speed) {
  uint8_t direction = (speed >= 0) ? 0x01 : 0x02;  // 0x01 = forward, 0x02 = reverse
  speed = abs(speed);                              // Ensure positive speed
  speed = map(speed, 0, 100, 0, 255);              // Scale speed to 0-255
  this->send_command_(CMD_MOTOR_B_SPEED, speed);
  this->send_command_(CMD_MOTOR_B_DIRECTION, direction);
}

void GroveMotorDriver::stop_motor_a() {
  this->send_command_(CMD_MOTOR_A_SPEED, 0);  // Speed = 0 to stop
}

void GroveMotorDriver::stop_motor_b() {
  this->send_command_(CMD_MOTOR_B_SPEED, 0);  // Speed = 0 to stop
}

void GroveMotorDriver::send_command_(uint8_t command, uint8_t value) {
  uint8_t data[2] = {command, value};
  this->write(data, 2);
}

}  // namespace grove_motor_driver
}  // namespace esphome
