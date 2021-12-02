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
            RC5 = run; // Skv documentation a ad vera RC4
            break;
        case 2: // Conv 2 forward
            RC2 = 0;
            RC3 = run;
            break;
        case 3:
            RC4 = run; // Skv documentation a ad vera RC5
            break;
        case 4: // Conv 2 reverse
            RC3 = 0;
            RC2 = run;
            break;
        case 5: // Stop all conveyors
            // Stop all individually, instead of PORTC = 0, because we don't
            // want to influence the turning of the turntable
            RC2 = 0;
            RC3 = 0;
            RC4 = 0;
            RC5 = 0;
            break;
        default:
            break;
    }
}

void TurnConveyor(short station) {
    RC0 = 0; // Turn off any movement
    RC1 = 0; // Turn off any movement
    struct sensorStruct sensors = ReadSensors(); // Read the sensors
    
    T2CON = (1<<SBIT_T2CKPS1);  // Timer2 with external freq and 16 as prescalar
    TMR2=100;  
    SetInterrupt(1); // Enable timer
    
    if (station == 0) { // 0 er CW
        if (sensors.conveyor2endstopCW == 0) {
            RC1 = 1; // Turn the conveyor CW
            while(sensors.conveyor2endstopCW == 0) { // Until we reach the endstop
                sensors = ReadSensors();
            } 
            RC1 = 0; // Stop the turning
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
    
    SetInterrupt(0); // Disable timer
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
    RE0 = 1;  // Send a signal to feeder
    __delay_ms(300); // Wait long enough for it to notice
    RE0 = 0; // Turn the signal off
}

void WaitForSensor(enum sensorEnum sensor) {
    struct sensorStruct sensors; // Sensor struct
    sensors = ReadSensors();
    
    if (sensor != sensors.button) { // We don't want to have a timeout on the button
        // Setup timeout
        T2CON = (1<<SBIT_T2CKPS1);  // Timer2 with external freq and 16 as prescalar
        TMR2=100;  
        SetInterrupt(1); // Enable timer
    }
   
    switch (sensor) {
        case conveyor1sensor1:
            while(sensors.conveyor1sensor1 == 0) { // Wait first sensor on conv1
                sensors = ReadSensors();
            }
            break;
        case conveyor1sensor2:
            while(sensors.conveyor1sensor2 == 0) {// Wait second sensor on conv1
                sensors = ReadSensors();
            }
            break;
        case conveyor2endstopCCW:
            while(sensors.conveyor2endstopCCW == 0) {// Wait endstop sensor CCW
                sensors = ReadSensors();
            }
            break;
        case conveyor2endstopCW:
            while(sensors.conveyor2endstopCW == 0) {// Wait endstop sensor CW
                sensors = ReadSensors();
            }
            break;
        case conveyor2sensor:
            while(sensors.conveyor2sensor == 0) {// Wait sensor on conv2
                sensors = ReadSensors();
            }
            break;
        case conveyor3sensor:
            while(sensors.conveyor3sensor == 0) {// Wait sensor on conv3
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
    
    SetInterrupt(0); // Disable timer interrupt
    
}
static int intCount;

void SetInterrupt(int value){
    intCount = 0;       // Reset the counter
    TMR2IE=value;       // Set status of timer interrupt bit in PIE1 register
    GIE=value;          //  Set status of  Global Interrupt
    PEIE=value;         //  Set status of  the Peripheral Interrupt
    TMR2ON = value;     //  Set status of  timer 2
}


// https://exploreembedded.com/wiki/PIC16f877a_Timer
void __interrupt() timer_isr()
{   
    if(TMR2IF==1)
    {
        TMR2 = 101;     /*Load the timer Value, (Note: Timervalue is 101 instead of 100 as the
                          Timer2 needs two instruction Cycles to start incrementing TMR2 */
        TMR2IF=0;       // Clear timer interrupt flag

        if(intCount>=3500) //1500us * 3500=525000us=5sec
        {
            intCount=0;
            lcd_clear();
            lcd_out(1,1,"Timer interrupt");
            lcd_out(2,1,"System halted!");
            PORTC = 0;
            
            SetInterrupt(0); // Disable timer interrupt
            while(1);
        }
        else
        {
            intCount++;  // Keep incrementing the count till it reaches 2000 to generate 1sec delay
        }
    } 
}

