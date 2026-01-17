#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <SoftwareSerial.h>

// --- PINS ---
#define PIN_ONE_WIRE      12
#define PIN_WINDOW_SERVO  50
#define PIN_DHT           52
#define PIN_RAIN_SENSOR   A0
#define PIN_LUM_EXT       A2
#define PIN_LUM_INT       A1
#define PIN_PIR_MOTION    38

#define LED_EXT_1         34
#define LED_EXT_2         26
#define LED_HEATING       28
#define LED_SALON_1       30
#define LED_SALON_2       32

// --- PARAMÈTRES ---
const float TEMP_HOT_LIMIT   = 24.0;
const float TEMP_COLD_ON     = 18.5;
const float TEMP_COLD_OFF    = 22.0;
const int   RAIN_LIMIT       = 650;
const int   LUM_NIGHT_LIMIT  = 200;
const unsigned long AUTO_LED_DELAY = 10000;

#endif