// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
/*
 * Lokaverkefni
Nafn: Emil
Dags: 18. nóvember 2021

PIC16F887
*/
#include "common.h" // Common definition and includes needed everywhere

void handleStateChange(enum State newState) {
    curState = newState;
}

void runCurrentState() {
    switch (curState) {
        case Menu:
            runMenuState();
            break;
        case Manual:
            runManualState();
            break;
        case Automatic:
            runAutomaticState();
            break;
    }
}

