// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
/*
 * Lokaverkefni
Nafn: Emil
Dags: 18. nóvember 2021

PIC16F887
*/
#include "common.h" // Common definition and includes needed everywhere

void hwSetup() {
// ===== uppsetning á PIC =====
	OSCCON = 0x75;	// Stillir klukkutíðni og skilgreinir hvaða klukka er notuð
	ANSEL  = 0x00;      // Skilgreinir alla pinna sem digital
	ANSELH = 0x00;      // Skilgreinir alla pinna sem (stafræna)
	CM1CON0 = CM1CON0 & 0x7F;  // Disable comparators
	CM2CON0 = CM2CON0 & 0x7F;  // Disable comparators
	INTCON = 0x00;      // Stillir interrupt bita

	PORTA = 0x00;       // Setur 0 á alla pinna á port A
	PORTB = 0x00;       // Setur 0 á alla pinna á port B
	PORTC = 0x00;       // Setur 0 á alla pinna á port C
	PORTD = 0x00;       // Setur 0 á alla pinna á port D
	PORTE = 0x00;       // Setur 0 á alla pinna á port E

	TRISA = 0xFF;       // Skilgreinir alla pinna á port A sem innganga
	TRISB = 0x00;       // Skilgreinir alla pinna á port B sem útganga
	TRISC = 0xFF;       // Skilgreinir alla pinna á port C sem útganga
	TRISD = 0x0F;       // RD0 ? RD3 eru  inngangar á PIC 
                        // RD4 ? RD7 eru útgangar á PIC
	TRISE = 0x00;       // Skilgreinir alla pinna á port E sem útganga

	lcd_init();				  		// uppsetning fyrir LCD skjá

}

