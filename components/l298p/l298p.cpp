#include "esphome/core/log.h"
#include "l298p.h"

namespace esphome {
namespace l298p {

static const char *TAG = "l298p.component";

void L298P::setup() {
  ESP_LOGI(TAG, "Setting up L298P Motor Controller...");
  // Perform any initial setup required for the motor controller
  this->set_motor_speed(MotorID::MOTOR1, 0);  // Ensure Motor1 is stopped
  this->set_motor_speed(MotorID::MOTOR2, 0);  // Ensure Motor2 is stopped
}

void L298P::loop() {
  // This is where you can handle periodic updates or checks
  // Example: Monitor motor status if feedback is available
}

void L298P::dump_config() {
  ESP_LOGCONFIG(TAG, "L298P Motor Controller:");
  ESP_LOGCONFIG(TAG, "  I2C Address: 0x%02X", this->address_);
}

void L298P::set_motor_speed(MotorID motor_id, uint8_t speed) {
  ESP_LOGI(TAG, "Setting motor %d speed to %d", static_cast<int>(motor_id), speed);
  uint8_t command[3] = {MotorSpeedSet, static_cast<uint8_t>(motor_id), speed};
  if (!this->write(command, sizeof(command))) {
    ESP_LOGE(TAG, "Failed to set motor %d speed", static_cast<int>(motor_id));
  }
}

void L298P::set_motor_direction(MotorDirection direction) {
  ESP_LOGI(TAG, "Setting motor direction to %s", 
           (direction == MotorDirection::ClockWise) ? "Clockwise" : "AntiClockwise");
  uint8_t command[2] = {DirectionSet, static_cast<uint8_t>(direction)};
  if (!this->write(command, sizeof(command))) {
    ESP_LOGE(TAG, "Failed to set motor direction");
  }
}

void L298P::stop_motor(MotorID motor_id) {
  ESP_LOGI(TAG, "Stopping motor %d", static_cast<int>(motor_id));
  this->set_motor_speed(motor_id, 0); // Reuse the set_motor_speed method to stop the motor
}

}  // namespace l298p
}  // namespace esphome
