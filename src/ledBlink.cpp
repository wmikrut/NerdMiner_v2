#include "ledBlink.h"

static bool     s_ledActive = false;
static uint32_t s_ledOffAt  = 0;

static inline void led_on() {
  gpio_set_level(LED_GPIO, LED_ACTIVE_HIGH ? 1 : 0);
}
static inline void led_off() {
  gpio_set_level(LED_GPIO, LED_ACTIVE_HIGH ? 0 : 1);
}

void led_blink_setup() {
  gpio_config_t io_conf = {};
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = (1ULL << LED_GPIO);
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en   = GPIO_PULLUP_DISABLE;
  gpio_config(&io_conf);

  led_off();
  s_ledActive = false;
  s_ledOffAt  = 0;
}

void led_blink_trigger(uint32_t onMs) {
  // Start (or extend) a blink without blocking the caller.
  s_ledActive = true;
  s_ledOffAt  = millis() + onMs;
  led_on();
}

void led_blink_service() {
  // Call this regularly from your main loop/tick.
  if (s_ledActive) {
    // signed subtraction to handle millis() wrap-around cleanly
    if ((int32_t)(millis() - s_ledOffAt) >= 0) {
      led_off();
      s_ledActive = false;
    }
  }
}
