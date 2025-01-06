#include "esphome/core/log.h"
#include "l298p.h"

namespace esphome {
namespace l298p {

static const char *TAG = "l298p";

void L298P::setup() {
  ESP_LOGI(TAG, "Setting up L298P Motor Controller...");
  this->set_motor_speed(1, 0);  // Ensure Motor 1 is stopped
  this->set_motor_speed(2, 0);  // Ensure Motor 2 is stopped
}

void L298P::loop() {
  // Add periodic tasks here if needed
}

void L298P::set_motor_speed(uint8_t motor_id, uint8_t speed) {
  ESP_LOGI(TAG, "Setting motor %d speed to %d", motor_id, speed);
  uint8_t command[3] = {0x82, motor_id, speed};  // 0x82: MotorSpeedSet command
  this->write(command, sizeof(command));
}

void L298P::set_motor_direction(uint8_t direction) {
  ESP_LOGI(TAG, "Setting motor direction to %d", direction);
  uint8_t command[2] = {0xAA, direction};  // 0xAA: DirectionSet command
  this->write(command, sizeof(command));
}

void L298P::stop_motor(uint8_t motor_id) {
  ESP_LOGI(TAG, "Stopping motor %d", motor_id);
  this->set_motor_speed(motor_id, 0);  // Reuse set_motor_speed to stop the motor
}

}  // namespace l298p
}  // namespace esphome
