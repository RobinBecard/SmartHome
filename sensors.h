#ifndef SENSORS_H
#define SENSORS_H

void initSensors();
float getInternalTemp();
void getExternalData(float *h, float *t);
bool checkRain();
int getExtLuminosity();
int getIntLuminosity();
bool checkMotion();

#endif