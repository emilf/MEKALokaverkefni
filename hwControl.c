// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
/*
 * Lokaverkefni
Nafn: Emil
Dags: 18. nóvember 2021

PIC16F887
*/
#include "common.h" // Common definition and includes needed everywhere

void ControlConveyor(short convNum, short stop) {
    static __bit run;
    run = !stop; // __bit has to be static, but it doesn't matter since we
                 // initialize it on each call.
                 // We reversing stop to run to make the code easier to read.
    switch(convNum) {
        case 1:
            RC4 = run;
            break;
        case 2: // Conv 2 forward
            RC3 = 0;
            RC2 = run;
            break;
        case 3:
            RC5 = run;
            break;
        case 4: // Conv 2 reverse
            RC2 = 0;
            RC3 = run;
            break;
        default:
            break;
    }
}

void TurnConveyor(short station) {
    RC0 = 0; // Turn off any movement
    RC1 = 0; // Turn off any movement
    struct sensorStruct sensors = ReadSensors(); // Read the sensors
    if (station == 0) { // 0 er CW
        if (sensors.conveyor2endstopCW == 0) {
            RC1 = 1; // Turn the conveyor CW
            while(sensors.conveyor2endstopCW == 0) { // Until we reach the endstop
                sensors = ReadSensors();
            } 
            RC0 = 1; // Stop the turning
        }
    }
    else if (station == 1) {
        if (sensors.conveyor2endstopCCW == 0) {
            RC0 = 1; // Turn the conveyor CCW
            while(sensors.conveyor2endstopCCW == 0) { // Until we reach the endstop
                sensors = ReadSensors();
            } 
            RC0 = 0; // Stop the turning
        }
    }    
}

struct sensorStruct ReadSensors() {
    struct sensorStruct retval; 
    
    retval.conveyor1sensor1 = RA4;
    retval.conveyor1sensor2 = RA5;
    retval.conveyor2endstopCCW = RA0;
    retval.conveyor2endstopCW = RA1;
    retval.conveyor2sensor = RA2;
    retval.conveyor3sensor = RA3;
    retval.button = RA7;
    return retval;
}


void FeedCube() {
    // Do nothing (yet)
    return;
}

void WaitForSensor(enum sensorEnum sensor) {
    struct sensorStruct sensors; // Sensor struct
    sensors = ReadSensors();
    switch (sensor) {
        case conveyor1sensor1:
            while(sensors.conveyor1sensor1 == 0) { // Wait for button press
                sensors = ReadSensors();
            }
            break;
        case conveyor1sensor2:
            while(sensors.conveyor1sensor2 == 0) { // Wait for button press
                sensors = ReadSensors();
            }
            break;
        case conveyor2endstopCCW:
            while(sensors.conveyor2endstopCCW == 0) { // Wait for button press
                sensors = ReadSensors();
            }
            break;
        case conveyor2endstopCW:
            while(sensors.conveyor2endstopCW == 0) { // Wait for button press
                sensors = ReadSensors();
            }
            break;
        case conveyor2sensor:
            while(sensors.conveyor2sensor == 0) { // Wait for button press
                sensors = ReadSensors();
            }
            break;
        case conveyor3sensor:
            while(sensors.conveyor3sensor == 0) { // Wait for button press
                sensors = ReadSensors();
            }
            break;
        case button:
            while(sensors.button == 0) { // Wait for button press
                sensors = ReadSensors();
            }
            break;
        default:
            break;        
    }    
}