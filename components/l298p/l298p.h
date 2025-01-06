#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace l298p {

constexpr uint8_t MotorSpeedSet = 0x82;
constexpr uint8_t DirectionSet = 0xaa;

enum class MotorID : uint8_t { MOTOR1 = 1, MOTOR2 = 2 };
enum class MotorDirection : uint8_t { ClockWise = 0x0a, AntiClockWise = 0x05 };

class l298p : public i2c::I2CDevice, public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  void set_motor_speed(MotorID motor_id, uint8_t speed);
  void set_motor_direction(MotorDirection direction);
  void stop_motor(MotorID motor_id);
};

}  // namespace l298p
}  // namespace esphome
