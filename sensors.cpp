#include "sensors.h"
#include "config.h"

DHT dht(PIN_DHT, DHT11);
OneWire oneWire(PIN_ONE_WIRE);
DallasTemperature dsSensors(&oneWire);

void initSensors() {
    dht.begin();
    dsSensors.begin();
    pinMode(PIN_RAIN_SENSOR, INPUT);
    pinMode(PIN_LUM_EXT, INPUT);
    pinMode(PIN_LUM_INT, INPUT);
    pinMode(PIN_PIR_MOTION, INPUT);
}

float getInternalTemp() {
    dsSensors.requestTemperatures();
    return dsSensors.getTempCByIndex(0);
}

void getExternalData(float *h, float *t) {
    *h = dht.readHumidity();
    *t = dht.readTemperature();
}

bool checkRain() {
    return analogRead(PIN_RAIN_SENSOR) <= RAIN_LIMIT;
}

int getExtLuminosity() {
    return (analogRead(PIN_LUM_EXT) < LUM_NIGHT_LIMIT) ? 0 : 1; 
}

int getIntLuminosity() {
    return (analogRead(PIN_LUM_INT) < 50) ? 0 : 1;
}

bool checkMotion() {
    return digitalRead(PIN_PIR_MOTION) == HIGH;
}