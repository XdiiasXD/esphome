#include "grove_motor_driver.h"
#include "esphome/core/log.h"

namespace esphome {
namespace grove_motor_driver {

void GroveMotorDriver::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Grove I2C Motor Driver...");
  // Stop both motors on setup
  this->stop_motor_a();
  this->stop_motor_b();
}

void GroveMotorDriver::loop() {
  // Optional: Add periodic checks or logic
}

void GroveMotorDriver::update() {
  ESP_LOGD(TAG, "Updating motor states...");
  // Optional: Monitor or log motor activity
}

void GroveMotorDriver::set_motor_a(int speed) {
  uint8_t direction = (speed >= 0) ? 0x01 : 0x02;  // 0x01 = forward, 0x02 = reverse
  speed = abs(speed);                              // Ensure positive speed
  speed = map(speed, 0, 100, 0, 255);              // Scale to 0-255

  if (speed != this->last_motor_a_speed_) {
    this->send_command_(CMD_MOTOR_A_SPEED, speed);
    this->send_command_(CMD_MOTOR_A_DIRECTION, direction);
    this->last_motor_a_speed_ = speed;
  }
}

void GroveMotorDriver::set_motor_b(int speed) {
  uint8_t direction = (speed >= 0) ? 0x01 : 0x02;  // 0x01 = forward, 0x02 = reverse
  speed = abs(speed);                              // Ensure positive speed
  speed = map(speed, 0, 100, 0, 255);              // Scale to 0-255

  if (speed != this->last_motor_b_speed_) {
    this->send_command_(CMD_MOTOR_B_SPEED, speed);
    this->send_command_(CMD_MOTOR_B_DIRECTION, direction);
    this->last_motor_b_speed_ = speed;
  }
}

void GroveMotorDriver::stop_motor_a() {
  this->send_command_(CMD_MOTOR_A_SPEED, 0);  // Speed = 0 to stop
  this->last_motor_a_speed_ = 0;
}

void GroveMotorDriver::stop_motor_b() {
  this->send_command_(CMD_MOTOR_B_SPEED, 0);  // Speed = 0 to stop
  this->last_motor_b_speed_ = 0;
}

void GroveMotorDriver::send_command_(uint8_t command, uint8_t value) {
  uint8_t data[2] = {command, value};
  if (!this->write(data, 2)) {
    ESP_LOGW(TAG, "Failed to send command 0x%02X with value 0x%02X", command, value);
  }
}

}  // namespace grove_motor_driver
}  // namespace esphome
