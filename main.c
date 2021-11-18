// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
/*
 * Lokaverkefni
Nafn: Emil
Dags: 18. nóvember 2021

PIC16F887
*/

// Includes
#include "common.h"

void main()             // Aðalforrit byrjar
{                       // Opnun á aðalforriti
    hwSetup();  // Sets up the hardware, ports and clocks and inits LCD
// ===== forritið byrjar =====
    
    drawMenu();
    
	while(1) {          // Endalaus lykkja 
        // The menu keyhandler always runs to allow abort in manual mode
        runCurrentState();
        __delay_ms(50); // We don't have to check as fast as possible. Lets save some power
	}								// while (1) lykkja endar
}									// main() endar



