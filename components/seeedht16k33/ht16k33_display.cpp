#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include "esphome/core/helpers.h"
#include "ht16k33_display.h"
#include "font.h"

#if defined(USE_ESP8266)
  #include <pgmspace.h>
#elif defined(USE_ESP32)
  #define PROGMEM
  #define pgm_read_word(addr) (*((const unsigned short*)(addr)))
#endif

namespace esphome {
namespace ht16k33_alpha {

static const char *const TAG = "ht16k33_alpha";

static const uint8_t DISPLAY_COMMAND_SET_DDRAM_ADDR = 0x00;
static const uint8_t DISPLAY_COMMAND_SYSTEM_SETUP = 0x21;
static const uint8_t DISPLAY_COMMAND_DISPLAY_OFF = 0x80;
static const uint8_t DISPLAY_COMMAND_DISPLAY_ON = 0x81;
static const uint8_t DISPLAY_COMMAND_DIMMING = 0xE0;

void HT16K33AlphaDisplay::setup() {
  this->write_bytes(DISPLAY_COMMAND_SYSTEM_SETUP, nullptr, 0);
  this->write_bytes(DISPLAY_COMMAND_DISPLAY_ON, nullptr, 0);
  this->set_brightness(1.0);
}

void HT16K33AlphaDisplay::loop() {}

float HT16K33AlphaDisplay::get_setup_priority() const { return setup_priority::PROCESSOR; }

void HT16K33AlphaDisplay::update() {
  this->call_writer();
}

void HT16K33AlphaDisplay::display_() {
  this->write_bytes(DISPLAY_COMMAND_SET_DDRAM_ADDR, this->buffer_, 16);
}

void HT16K33AlphaDisplay::set_brightness(float level) {
  int val = (int) round(level * 16);
  if (val < 0)
    val = 0;
  if (val > 16)
    val = 16;
  this->brightness_ = val;
  
  if (val == 0) {
    this->write_bytes(DISPLAY_COMMAND_DISPLAY_OFF, nullptr, 0);
  } else {
    this->write_bytes(DISPLAY_COMMAND_DIMMING + (val - 1), nullptr, 0);
    this->write_bytes(DISPLAY_COMMAND_DISPLAY_ON, nullptr, 0);
  }
}

float HT16K33AlphaDisplay::get_brightness() {
  return this->brightness_ / 16.0;
}

void HT16K33AlphaDisplay::print(const char *str) {
  if (tube_type_ == TYPE_2) {
    handle_2tube_display_(str);
  } else {
    handle_4tube_display_(str);
  }
}

void HT16K33AlphaDisplay::handle_2tube_display_(const char* str) {
  memset(buffer_, 0, sizeof(buffer_));
  int len = strlen(str);
  if (len > 2) len = 2;
  
  for (int i = 0; i < len; i++) {
    char c = str[i];
    uint16_t value;
    
    if (c >= '0' && c <= '9') {
      value = pgm_read_word(&g_display_font2[c - '0' + 2]);
      ESP_LOGD(TAG, "Digit %c mapped to value: 0x%04X", c, value);
    } else if (c >= 'A' && c <= 'Z') {
      value = pgm_read_word(&g_display_font2[c - 'A' + 12]);
    } else if (c >= 'a' && c <= 'z') {
      value = pgm_read_word(&g_display_font2[c - 'a' + 12]);
    } else if (c == '.') {
      value = pgm_read_word(&g_display_font2[0]);
    } else {
      value = 0;
    }
    
    // Write to positions 4,5 and 2,3 instead of 0,1 and 2,3
    int base_pos = (i == 0) ? 4 : 2;
    buffer_[base_pos] = value >> 8;
    buffer_[base_pos + 1] = value & 0xFF;
    
    ESP_LOGD(TAG, "Position %d: buffer[%d]=0x%02X buffer[%d]=0x%02X", 
             i, base_pos, buffer_[base_pos], base_pos+1, buffer_[base_pos+1]);
  }
  
  display_();
}

void HT16K33AlphaDisplay::handle_4tube_display_(const char* str) {
  memset(buffer_, 0, sizeof(buffer_));
  uint16_t fontc;
  int offset = 0;
  
  while (*str != '\0' && offset < 8) {
    uint8_t c = *reinterpret_cast<const uint8_t *>(str++);
    if (c > 127)
      fontc = 0;
    else
      fontc = pgm_read_word(&alphafonttable[c]);
    
    c = *reinterpret_cast<const uint8_t *>(str);
    if (c == '.') {
      fontc |= 0x4000;
      str++;
    }
    
    this->buffer_[offset++] = fontc & 0xff;
    this->buffer_[offset++] = fontc >> 8;
  }
  
  display_();
}

void HT16K33AlphaDisplay::print(const std::string &str) { this->print(str.c_str()); }

void HT16K33AlphaDisplay::printf(const char *format, ...) {
  va_list arg;
  va_start(arg, format);
  char buffer[64];
  int ret = vsnprintf(buffer, sizeof(buffer), format, arg);
  va_end(arg);
  if (ret > 0)
    this->print(buffer);
}

#ifdef USE_TIME
void HT16K33AlphaDisplay::strftime(const char *format, ESPTime time) {
  char buffer[64];
  size_t ret = time.strftime(buffer, sizeof(buffer), format);
  if (ret > 0)
    this->print(buffer);
}
#endif

}  // namespace ht16k33_alpha
}  // namespace esphome