#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace l298p {

class L298P : public i2c::I2CDevice, public Component {
 public:
  void setup() override;
  void loop() override;

  void set_motor_speed(uint8_t motor_id, uint8_t speed);
  void set_motor_direction(uint8_t direction);
  void stop_motor(uint8_t motor_id);
};

}  // namespace l298p
}  // namespace esphome
