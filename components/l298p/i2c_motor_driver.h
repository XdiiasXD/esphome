#pragma once

#include "esphome.h"
#include "Grove_I2C_Motor_Driver.h"

class I2CMotorDriverComponent : public Component {
public:
    void setup() override {
        Motor.begin(0x0F); // Initialize with the default I2C address
        ESP_LOGI("I2C Motor Driver", "Motor driver initialized");
    }

    void loop() override {
        // Add any repetitive tasks if needed
    }

    void set_motor_speed(uint8_t motor_id, int speed) {
        Motor.speed(motor_id, speed);
    }

    void stop_motor(uint8_t motor_id) {
        Motor.stop(motor_id);
    }
};
