#pragma once
#include <Arduino.h>
#include "driver/gpio.h"

// === CONFIG ===
// Change these two to match your board wiring:
#ifndef LED_GPIO
#define LED_GPIO GPIO_NUM_2      // built-in LED on many ESP32 dev boards
#endif

#ifndef LED_ACTIVE_HIGH
#define LED_ACTIVE_HIGH 1        // set to 0 if your LED is active-low
#endif
// ==============

void led_blink_setup();
void led_blink_trigger(uint32_t onMs = 100);
void led_blink_service();