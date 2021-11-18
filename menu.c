// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
/*
 * Lokaverkefni
Nafn: Emil
Dags: 18. nóvember 2021

PIC16F887
*/
#include "common.h" // Common definition and includes needed everywhere

void drawMenu(){
    lcd_out(1,1,"A: Auto         ");
    lcd_out(2,1,"B: Manual       ");
}

void handleMenuKeypress(){
    int keyVal = -1;
    keyVal = readKeypad();
    
    if (curState != Menu) return;
    
    if (keyVal == 0x0A) {
        waitUntilKeyUp();
        handleStateChange(Automatic);
    }
    if (keyVal == 0x0B) {
        waitUntilKeyUp();
        handleStateChange(Manual);
    }
}

void runMenuState() {
    drawMenu();
    handleMenuKeypress();
}
