// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
/*
 * Lokaverkefni
Nafn: Emil
Dags: 18. nóvember 2021

PIC16F887
*/
#include "common.h" // Common definition and includes needed everywhere

int readKeypad() {
    unsigned short keypadValue = 0; // Fyrir keypad bitmap
    unsigned short numericValue = 0; // Fyrir keypad value mappað
    PORTD = 0; // Byrjum á að hreinsa til

    // Lesum fyrstu linu
    RD4 = 1; // Opnum fyrstu línuna
    __delay_ms(1); // Og hinkrum smá
    keypadValue = PORTD & 0x0F; // Fjalægjum RD4-RD7 úr niðurstöðunni
    __delay_ms(1); // Og hinkrum smá

    // Lesum aðra línu
    RD4 = 0; // Lokum fyrstu línu
    RD5 = 1; // Og opnum aðra
    __delay_ms(1); // Og hinkrum smá
    keypadValue = keypadValue + ((PORTD & 0x0F) << 4); // Fjalægjum RD4-RD7 úr niðurstöðunni
    // og færum okkur um 4 sæti til vinsti
    __delay_ms(1); // Og hinkrum smá

    // Lesum þriðju línu
    RD5 = 0; // Lokum annari línu
    RD6 = 1; // Og opnum þriðju
    __delay_ms(1); // Og hinkrum smá
    keypadValue = keypadValue + ((PORTD & 0x0F) << 8); // Fjalægjum RD4-RD7 úr niðurstöðunni
    // og færum okkur um 8 sæti til vinsti

    // Lesum fjórðu línu
    __delay_ms(1); // Og hinkrum smá
    RD6 = 0; // Lokum þriðju línunni
    RD7 = 1; // Og opnum fjórðu
    __delay_ms(1); // Og hinkrum smá
    keypadValue = keypadValue + ((PORTD & 0x0F) << 12); // Fjalægjum RD4-RD7 úr niðurstöðunni
    // og færum okkur um 12 sæti til vinsti

    switch (keypadValue) { // Map til að breyta þessu úr bitmap í tölu
        case 0x0: // If the value is 0, no button is being pressed
            // We just want to show the last value entered
            numericValue = -1;
            break; // And stop processing the switch
        case 0x01: // Button 1          
            numericValue = 0x1; // Maps to 1
            break; // And stop processing the switch
        case 0x02: // Button 2
            numericValue = 0x2; // Maps to 2
            break; // And stop processing the switch
        case 0x04: // Button 3
            numericValue = 0x3; // Maps to 3
            break; // And stop processing the switch
        case 0x08: // Button A
            numericValue = 0xA; // Maps to 0xA
            break; // And stop processing the switch
        case 0x10: // Button 4
            numericValue = 0x4; // Maps to 4
            break; // And stop processing the switch
        case 0x20: // Button 5
            numericValue = 0x5; // Maps to 5
            break; // And stop processing the switch
        case 0x40: // Button 6
            numericValue = 0x6; // Maps to 6
            break; // And stop processing the switch
        case 0x80: // Button B
            numericValue = 0xB; // Maps to 0xB
            break; // And stop processing the switch
        case 0x100: // Button 7
            numericValue = 0x7; // Maps to 7
            break; // And stop processing the switch
        case 0x200: // Button 8
            numericValue = 0x8; // Maps to 8
            break; // And stop processing the switch
        case 0x400: // Button 9
            numericValue = 0x9; // Maps to 9
            break; // And stop processing the switch
        case 0x800: // Button C
            numericValue = 0xC; // Maps to 0xC
            break; // And stop processing the switch
        case 0x1000: // Button *
            numericValue = 0xE; // We map it to 0xE
            break; // And stop processing the switch
        case 0x2000: // Button 0
            numericValue = 0x0; // Maps to 0
            break; // And stop processing the switch
        case 0x4000: // Button #
            numericValue = 0xF; // We map it to 0xF
            break; // And stop processing the switch
        case 0x8000: // Button D
            numericValue = 0xD; // Maps to 0xD
            break; // And stop processing the switch
    } // switch endar

    //PORTC = numericValue; // Skilum þessu út í PORTC
    return numericValue; // og ut ur fallinu
} // ReadKeypad endar

void waitUntilKeyUp() {
    PORTD = 0xF0;
    while (PORTD & 0x0F) {}
}

