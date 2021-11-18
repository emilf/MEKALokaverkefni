// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
/*
 * Lokaverkefni
Nafn: Emil
Dags: 18. n�vember 2021

PIC16F887
*/
#include "common.h" // Common definition and includes needed everywhere

int readKeypad() {
    unsigned short keypadValue = 0; // Fyrir keypad bitmap
    unsigned short numericValue = 0; // Fyrir keypad value mappa�
    PORTD = 0; // Byrjum � a� hreinsa til

    // Lesum fyrstu linu
    RD4 = 1; // Opnum fyrstu l�nuna
    __delay_ms(1); // Og hinkrum sm�
    keypadValue = PORTD & 0x0F; // Fjal�gjum RD4-RD7 �r ni�urst��unni
    __delay_ms(1); // Og hinkrum sm�

    // Lesum a�ra l�nu
    RD4 = 0; // Lokum fyrstu l�nu
    RD5 = 1; // Og opnum a�ra
    __delay_ms(1); // Og hinkrum sm�
    keypadValue = keypadValue + ((PORTD & 0x0F) << 4); // Fjal�gjum RD4-RD7 �r ni�urst��unni
    // og f�rum okkur um 4 s�ti til vinsti
    __delay_ms(1); // Og hinkrum sm�

    // Lesum �ri�ju l�nu
    RD5 = 0; // Lokum annari l�nu
    RD6 = 1; // Og opnum �ri�ju
    __delay_ms(1); // Og hinkrum sm�
    keypadValue = keypadValue + ((PORTD & 0x0F) << 8); // Fjal�gjum RD4-RD7 �r ni�urst��unni
    // og f�rum okkur um 8 s�ti til vinsti

    // Lesum fj�r�u l�nu
    __delay_ms(1); // Og hinkrum sm�
    RD6 = 0; // Lokum �ri�ju l�nunni
    RD7 = 1; // Og opnum fj�r�u
    __delay_ms(1); // Og hinkrum sm�
    keypadValue = keypadValue + ((PORTD & 0x0F) << 12); // Fjal�gjum RD4-RD7 �r ni�urst��unni
    // og f�rum okkur um 12 s�ti til vinsti

    switch (keypadValue) { // Map til a� breyta �essu �r bitmap � t�lu
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

    //PORTC = numericValue; // Skilum �essu �t � PORTC
    return numericValue; // og ut ur fallinu
} // ReadKeypad endar

void waitUntilKeyUp() {
    PORTD = 0xF0;
    while (PORTD & 0x0F) {}
}

