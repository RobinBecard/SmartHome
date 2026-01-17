/**
 * Smart Home Control System - Main Firmware
 * Author: Robin Bécard
 * Target: Arduino Mega 2560
 * * This file manages the main state machine and handles communication 
 * between the mobile app and the modular hardware components.
 */

#include "config.h"
#include "sensors.h"
#include "actuators.h"

// --- Global States ---
int currentCommand = -1;
bool isAutoMode = false;
unsigned long lastTelemetryTime = 0;
const unsigned long TELEMETRY_INTERVAL = 2000; // Send data every 2s

void setup() {
    // Initialize Serial Communications
    Serial.begin(9600);   // Debugging (USB)
    Serial1.begin(9600);  // App Communication (Bluetooth/Wifi)
    
    // Initialize Hardware Modules
    initSensors();
    initActuators();
    
    // Safety: Close window on startup
    setWindow(false);
    
    Serial.println(F("--- Smart Home System Ready ---"));
}

void loop() {
    // 1. Read Commands from App
    if (Serial1.available() > 0) {
        currentCommand = Serial1.read();
        handleAppCommand(currentCommand);
    }

    // 2. Manage Modes
    if (isAutoMode) {
        executeAutoLogic();
    }

    // 3. Periodic Telemetry (Non-blocking)
    if (millis() - lastTelemetryTime >= TELEMETRY_INTERVAL) {
        sendTelemetry();
        lastTelemetryTime = millis();
    }
    
    // Minor delay for system stability
    delay(10);
}

/**
 * Handle manual commands received from the Serial1 interface
 */
void handleAppCommand(int cmd) {
    Serial.print(F("Command received: "));
    Serial.println(cmd);

    switch(cmd) {
        case 17: isAutoMode = true;  Serial.println(F("Mode: AUTO")); break;
        case 16: isAutoMode = false; Serial.println(F("Mode: MANUAL")); break;
        
        // Interior Lighting
        case 3:  setLedSalon(true);  break;
        case 2:  setLedSalon(false); break;
        case 5:  setLedSalon(true);  break; // Duplicate in original code for salon2
        case 4:  setLedSalon(false); break;

        // Exterior Lighting
        case 9:  setLedExt(true);    break;
        case 8:  setLedExt(false);   break;
        case 11: setLedExt(true);    break;
        case 10: setLedExt(false);   break;

        // Climate Control
        case 13: setHeating(true);   break;
        case 12: setHeating(false);  break;
        case 15: setWindow(true);    break;
        case 14: setWindow(false);   break;

        default: break; 
    }
}

/**
 * Smart Logic: Automatically manages actuators based on sensor data
 */
void executeAutoLogic() {
    float t_int = getInternalTemp();
    bool rain = checkRain();
    int lum_ext = getExtLuminosity();
    bool motion = checkMotion();

    // Window Logic (Close if raining or too cold)
    if (t_int >= TEMP_HOT_LIMIT && !rain) {
        setWindow(true);
    } else {
        setWindow(false);
    }

    // Heating Logic
    if (t_int < TEMP_COLD_ON) {
        setHeating(true);
    } else if (t_int > TEMP_COLD_OFF) {
        setHeating(false);
    }

    // Exterior Lighting (Night + Motion)
    if (lum_ext == 1 && motion) {
        setLedExt(true);
    } else {
        setLedExt(false);
    }
}

/**
 * Transmit real-time sensor data to the mobile application
 */
void sendTelemetry() {
    float t_int = getInternalTemp();
    float t_ext, hum_ext;
    getExternalData(&hum_ext, &t_ext);
    bool raining = checkRain();

    // Format: TempInt|TempExt|HumExt|RainStatus
    Serial1.print(t_int);    Serial1.print(F("|"));
    Serial1.print(t_ext);    Serial1.print(F("|"));
    Serial1.print(hum_ext);  Serial1.print(F("|"));
    Serial1.println(raining ? 1 : 0);
}