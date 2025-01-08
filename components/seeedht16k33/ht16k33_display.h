#pragma once
#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/components/i2c/i2c.h"
#ifdef USE_TIME
#include "esphome/components/time/real_time_clock.h"
#include "esphome/core/time.h"
#endif

namespace esphome {
namespace ht16k33_alpha {

enum TubeType {
  TYPE_2 = 0,
  TYPE_4 = 1
};

class HT16K33AlphaDisplay : public PollingComponent, public i2c::I2CDevice {
 public:
  HT16K33AlphaDisplay() : tube_type_(TYPE_2) {}
  void set_writer(std::function<void(HT16K33AlphaDisplay &)> &&writer) { this->writer_ = std::move(writer); }
  void setup() override;
  void loop() override;
  float get_setup_priority() const override;
  void update() override;
  void set_brightness(float level);
  float get_brightness();
  void print(const char *str);
  void print(const std::string &str);
  void printf(const char *format, ...) __attribute__((format(printf, 2, 3)));
#ifdef USE_TIME
  void strftime(const char *format, ESPTime time) __attribute__((format(strftime, 2, 0)));
#endif

 protected:
  void command_(uint8_t value);
  void call_writer() { this->writer_(*this); }
  void display_();
  std::function<void(HT16K33AlphaDisplay &)> writer_;
  uint8_t buffer_[16];
  uint8_t brightness_{16};
  TubeType tube_type_;
  void handle_2tube_display_(const char* str);
  void handle_4tube_display_(const char* str);
};

}  // namespace ht16k33_alpha
}  // namespace esphome