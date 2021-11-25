// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
/*
 * Lokaverkefni
Nafn: Emil
Dags: 18. nóvember 2021

PIC16F887
*/

#include "common.h" // Common definition and includes needed everywhere

void drawManual(){
    lcd_out(1, 1, "Number keys turn");
    lcd_out(2, 1, "on pins   D=Menu");
}

void handleManualKeypress(){
    int keyVal = -1;
    keyVal = readKeypad();
    
    if (curState != Manual) return;
    
    switch(keyVal) { // Handle each key
        case 0x0D:
            waitUntilKeyUp();
            handleStateChange(Menu);
            break;
        case 0:
            PortC_Utg_0 = 1;
            break;
        case 1:
            PortC_Utg_1 = 1;
            break;
        case 2:
            PortC_Utg_2 = 1;
            break;
        case 3:
            PortC_Utg_3 = 1;
            break;
        case 4:
            PortC_Utg_4 = 1;
            break;
        case 5:
            PortC_Utg_5 = 1;
            break;
        case 6:
            PortC_Utg_6 = 1;
            break;
        case 7:
            PortC_Utg_7 = 1;
            break;            
        default:
            PORTC = 0; // Turn off all outputs if no key or invalid key is pressed
    }
}

void runManualState() {
    drawManual();
    handleManualKeypress();
}

