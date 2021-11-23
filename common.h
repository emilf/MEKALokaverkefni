// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
/*
 * Lokaverkefni
Nafn: Emil
Dags: 18. nóvember 2021

PIC16F887
*/

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif



// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdio.h>
#include <string.h>

#define _XTAL_FREQ 8000000 // Indicates the system frequency to the compiler

#pragma config FOSC = INTRC_NOCLKOUT  // Internal Osc RA6 og RA7 = I/O
#pragma config WDTE = OFF  // Disable Watchdog Timer.
#pragma config PWRTE = ON  // Enable Power Up Timer.
#pragma config MCLRE = ON  // Enable Master Clear.
#pragma config CP = OFF    // Disable Code Protect.
#pragma config BOREN = ON  // Enable Brown Out Reset.
#pragma config IESO = ON   // Enable Int-Ext Switchover.
#pragma config FCMEN = ON  // Enable Fail-safe Clk. Monitor.
#pragma config LVP = OFF   // Disable Low Voltage Program.
#pragma config DEBUG = OFF // Disable In-Circuit Debugger.
#pragma config BOR4V = BOR40V // Brown-out Reset Sel.

#define PortC_Utg_0 RC0
#define PortC_Utg_1 RC1
#define PortC_Utg_2 RC2
#define PortC_Utg_3 RC3
#define PortC_Utg_4 RC4
#define PortC_Utg_5 RC5
#define PortC_Utg_6 RC6
#define PortC_Utg_7 RC7

#define PortA_Inn_0 RA0
#define PortA_Inn_1 RA1
#define PortA_Inn_2 RA2
#define PortA_Inn_3 RA3
#define PortA_Inn_4 RA4
#define PortA_Inn_5 RA5
#define PortA_Inn_6 RA6
#define PortA_Inn_7 RA7

enum State { Menu, Manual, Automatic} curState = Menu;

// lcd.c
void lcd_write(unsigned char);
void lcd_clear(void);
void lcd_out( unsigned char line, unsigned char character, const char * s);
void lcd_goto(unsigned char pos);
void lcd_init(void);
void lcd_chr_cp(char);
void lcd_cmd(unsigned char);
void lcd_chr( unsigned char line, unsigned char character, char c );

// readKeypad.c
int readKeypad(void);
void waitUntilKeyUp(void);

// hwSetup.c
void hwSetup(void);

// hwControl.c
#define SBIT_PS2  2
#define SBIT_T2CKPS1  1
void __interrupt() timer_isr(void);
void SetInterrupt(int);

struct sensorStruct {
   short conveyor1sensor1;
   short conveyor1sensor2;
   short conveyor2sensor;
   short conveyor3sensor;
   short conveyor2endstopCCW;
   short conveyor2endstopCW;
   short button;
}; 
enum sensorEnum {
   conveyor1sensor1,
   conveyor1sensor2,
   conveyor2sensor,
   conveyor3sensor,
   conveyor2endstopCCW,
   conveyor2endstopCW,
   button
}; 

void ControlConveyor(short, short);
void TurnConveyor(short);
struct sensorStruct ReadSensors(void);
void FeedCube(void);


// menu.c
void drawMenu(void);
void handleMenuKeypress(void);
void runMenuState(void);

// stateManager.c
void handleStateChange(enum State);
void runCurrentState(void);

// manual.c
void runManualState(void);

// automatic.c
enum autostate {
    Idle, 
    Cube1DataEntry,
    Cube2DataEntry,
    Cube3DataEntry,
    Cube4DataEntry,
    WaitForStart,
    PositionConv2StartPos,
    RunConv1, 
    DoFeedCube,
    WaitForSensorConv1Sensor1,
    WaitForSensorConv1Sensor2,
    RunConv2First,
    WaitForSensorConv2Sensor,
    PositionConv2FeedPos,
    RunConv2Continue,
    RunConv3,
    WaitForSensorConv3Sensor,
    NextCube,
    End
};
short cubeData[4];
short curCube;

void runAutomaticState(void);
void SaveCubeDestination(short);
void WaitForSensor(enum sensorEnum);

#endif	/* XC_HEADER_TEMPLATE_H */




#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

