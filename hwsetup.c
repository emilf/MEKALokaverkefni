// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
/*
 * Lokaverkefni
Nafn: Emil
Dags: 18. n�vember 2021

PIC16F887
*/
#include "common.h" // Common definition and includes needed everywhere

void hwSetup() {
// ===== uppsetning � PIC =====
	OSCCON = 0x75;	// Stillir klukkut��ni og skilgreinir hva�a klukka er notu�
	ANSEL  = 0x00;      // Skilgreinir alla pinna sem digital
	ANSELH = 0x00;      // Skilgreinir alla pinna sem (stafr�na)
	CM1CON0 = CM1CON0 & 0x7F;  // Disable comparators
	CM2CON0 = CM2CON0 & 0x7F;  // Disable comparators
	INTCON = 0x00;      // Stillir interrupt bita

	PORTA = 0x00;       // Setur 0 � alla pinna � port A
	PORTB = 0x00;       // Setur 0 � alla pinna � port B
	PORTC = 0x00;       // Setur 0 � alla pinna � port C
	PORTD = 0x00;       // Setur 0 � alla pinna � port D
	PORTE = 0x00;       // Setur 0 � alla pinna � port E

	TRISA = 0xFF;       // Skilgreinir alla pinna � port A sem innganga
	TRISB = 0x00;       // Skilgreinir alla pinna � port B sem �tganga
	TRISC = 0xFF;       // Skilgreinir alla pinna � port C sem �tganga
	TRISD = 0x0F;       // RD0 ? RD3 eru  inngangar � PIC 
                        // RD4 ? RD7 eru �tgangar � PIC
	TRISE = 0x00;       // Skilgreinir alla pinna � port E sem �tganga

	lcd_init();				  		// uppsetning fyrir LCD skj�

}

