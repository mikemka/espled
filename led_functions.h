#ifndef LED_FUNCTIONS_H
#define LED_FUNCTIONS_H
#include <Arduino.h>


void setupLEDPins ();
void write5v (int r_value, int g_value, int b_value);
void write12v (int r_value, int g_value, int b_value);
int clamp (int value, int min_value, int max_value);
void processColor(int ms, int iter, int r_value, int g_value, int b_value, bool led_5v);


#endif
