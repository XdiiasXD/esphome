namespace esphome {
namespace l298p {

constexpr uint8_t MotorSpeedSet = 0x82;
constexpr uint8_t DirectionSet = 0xaa;

enum class MotorID : uint8_t { MOTOR1 = 1, MOTOR2 = 2 };
enum class MotorDirection : uint8_t { ClockWise = 0x0a, AntiClockWise = 0x05 };

class l298p : public i2c::I2CDevice, public Component {
 public:
  void setup() override {
    ESP_LOGI("l298p", "Setting up L298P Motor Controller...");
  }

  void loop() override {
    // Add logic to control motors or handle periodic updates
  }

  void dump_config() override {
    ESP_LOGCONFIG("l298p", "L298P Motor Controller:");
    ESP_LOGCONFIG("l298p", "  Address: 0x%02X", this->address_);
  }

  void set_motor_speed(MotorID motor_id, uint8_t speed) {
    uint8_t command[3] = {MotorSpeedSet, static_cast<uint8_t>(motor_id), speed};
    if (this->write(command, sizeof(command))) {
      ESP_LOGI("l298p", "Set motor %d speed to %d", static_cast<int>(motor_id), speed);
    } else {
      ESP_LOGE("l298p", "Failed to set motor %d speed", static_cast<int>(motor_id));
    }
  }

  void set_motor_direction(MotorDirection direction) {
    uint8_t command[2] = {DirectionSet, static_cast<uint8_t>(direction)};
    if (this->write(command, sizeof(command))) {
      ESP_LOGI("l298p", "Set motor direction to %d", static_cast<int>(direction));
    } else {
      ESP_LOGE("l298p", "Failed to set motor direction");
    }
  }

  void stop_motor(MotorID motor_id) {
    uint8_t command[3] = {MotorSpeedSet, static_cast<uint8_t>(motor_id), 0}; // Set speed to 0
    if (this
