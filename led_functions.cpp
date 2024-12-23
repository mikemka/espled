#include "led_functions.h"
#include "settings.h"


void setupLEDPins () {
  pinMode(LED_5V_G, OUTPUT);
  pinMode(LED_5V_R, OUTPUT);
  pinMode(LED_5V_B, OUTPUT);

  pinMode(LED_12V_G, OUTPUT);
  pinMode(LED_12V_R, OUTPUT);
  pinMode(LED_12V_B, OUTPUT);
}

void write5v (int r_value, int g_value, int b_value) {
  analogWrite(LED_5V_G, clamp(255 - g_value, 0, 255));
  analogWrite(LED_5V_R, clamp(255 - r_value, 0, 255));
  analogWrite(LED_5V_B, clamp(255 - b_value, 0, 255));
}


void write12v (int r_value, int g_value, int b_value) {
  analogWrite(LED_12V_G, clamp(255 - g_value, 0, 255));
  analogWrite(LED_12V_R, clamp(255 - r_value, 0, 255));
  analogWrite(LED_12V_B, clamp(255 - b_value, 0, 255));
}


int clamp (int value, int min_value, int max_value) {
  return max(min_value, min(max_value, value));
}


void processColor(int ms, int iter, int r_value, int g_value, int b_value, bool led_5v) {
  for (int led = 0; led < iter * 2; ++led) {
    delay(ms / iter);
    write5v(!(led % 2) * r_value * led_5v, !(led % 2) * g_value * led_5v, !(led % 2) * b_value * led_5v);
  }
}
