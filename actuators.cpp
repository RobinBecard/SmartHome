#include "actuators.h"
#include "config.h"

Servo windowServo;

void initActuators() {
    windowServo.attach(PIN_WINDOW_SERVO);
    pinMode(LED_EXT_1, OUTPUT);
    pinMode(LED_EXT_2, OUTPUT);
    pinMode(LED_HEATING, OUTPUT);
    pinMode(LED_SALON_1, OUTPUT);
    pinMode(LED_SALON_2, OUTPUT);
}

void setWindow(bool open) {
    if(open) windowServo.write(0);
    else windowServo.write(180);
}

void setLedExt(bool state) {
    digitalWrite(LED_EXT_1, state);
    digitalWrite(LED_EXT_2, state);
}

void setLedSalon(bool state) {
    digitalWrite(LED_SALON_1, state);
    digitalWrite(LED_SALON_2, state);
}

void setHeating(bool state) {
    digitalWrite(LED_HEATING, state);
}