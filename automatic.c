// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
/*
 * Lokaverkefni
Nafn: Emil
Dags: 18. nóvember 2021

PIC16F887
*/

#include "common.h" // Common definition and includes needed everywhere
/* Copied from common.h for reference
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
*/

void runAutomaticControl() {
    struct sensorStruct sensors; // Sensor struct
    enum autostate curAutoState = Idle;
    char str[17]; // Buffer for line for screen
    curCube = 1;
    // ===== forritið byrjar =====
    while(1) {
        switch (curAutoState) {
            case Idle:
                lcd_clear();
                lcd_out(1,1, "Automatic mode");
                lcd_out(2,1, "Press any key ");

                while(readKeypad() == -1); // Wait for any key
                waitUntilKeyUp(); // Wait until it's released
                curAutoState = Cube1DataEntry;
                __delay_ms(300);
                break;
            case Cube1DataEntry:
                SaveCubeDestination(1);
                curAutoState = Cube2DataEntry;
                __delay_ms(300);
                break;
            case Cube2DataEntry:
                SaveCubeDestination(2);
                curAutoState = Cube3DataEntry;
                __delay_ms(300);
                break;
            case Cube3DataEntry:
                SaveCubeDestination(3);
                curAutoState = Cube4DataEntry;
                __delay_ms(300);
                break;
            case Cube4DataEntry:
                SaveCubeDestination(4);
                curAutoState = WaitForStart;
                __delay_ms(300);
                break;
            case WaitForStart:
                lcd_clear();
                lcd_out(1,1, "Press the START");
                lcd_out(2,1, "button on device");
                sensors = ReadSensors();
                while(sensors.button == 0) { // Wait for button press
                    sensors = ReadSensors();
                } 
                while(sensors.button == 1) { // and for it to be released
                    sensors = ReadSensors();
                } 
                curAutoState = PositionConv2StartPos;
                __delay_ms(300);
                break;
            case PositionConv2StartPos:
                lcd_clear();
                lcd_out(1,1,"Positioning");
                lcd_out(2,1,"turntable");
                TurnConveyor(0);
                curAutoState = RunConv1;
                __delay_ms(300);
                break;
            case RunConv1:
                lcd_clear();
                lcd_out(1,1,"Run conveyor 1");
                ControlConveyor(1,0);
                curAutoState = DoFeedCube;
                __delay_ms(300);
                break;
            case DoFeedCube:
                lcd_clear();
                lcd_out(1,1,"Feed cube");
                FeedCube();
                curAutoState = WaitForSensorConv1Sensor1;
                __delay_ms(300);
                break;
            case WaitForSensorConv1Sensor1:
                lcd_clear();
                lcd_out(1,1,"Waiting for");
                lcd_out(2,1,"conv 1 sensor 1");
                WaitForSensor(conveyor1sensor1);
                curAutoState = WaitForSensorConv1Sensor2;
                __delay_ms(300);
                break;
            case WaitForSensorConv1Sensor2:
                lcd_clear();
                lcd_out(1,1,"Waiting for");
                lcd_out(2,1,"conv 1 sensor 2");
                WaitForSensor(conveyor1sensor2);
                curAutoState = RunConv2First;
                __delay_ms(300);
                break;
            case RunConv2First:
                lcd_clear();
                lcd_out(1,1,"Run conveyor 2");
                lcd_out(2,1,"First run");
                ControlConveyor(2,0);
                curAutoState = WaitForSensorConv2Sensor;
                __delay_ms(300);
                break;
            case WaitForSensorConv2Sensor:
                lcd_clear();
                lcd_out(1,1,"Waiting for");
                lcd_out(2,1,"conv 2 sensor");
                WaitForSensor(conveyor2sensor);
                ControlConveyor(2,1);
                curAutoState = PositionConv2FeedPos;
                __delay_ms(300);
                break;
            case PositionConv2FeedPos:
                lcd_clear();
                lcd_out(1,1,"Positioning");
                lcd_out(2,1,"turntable 2");
                if (cubeData[curCube-1] != 2) {
                    TurnConveyor(1);
                }
                curAutoState = RunConv2Continue;
                __delay_ms(300);
                break;
            case RunConv2Continue:
                lcd_clear();
                lcd_out(1,1,"Run conveyor 2");
                lcd_out(2,1,"Continue");
                if (cubeData[curCube-1] == 1) {
                    ControlConveyor(2,0);
                    curAutoState = NextCube;
                    __delay_ms(1200);
                    break;
                }
                else if (cubeData[curCube-1] == 3) {
                    ControlConveyor(4,0);
                    curAutoState = RunConv3;
                    break;
                }
                // If destination is 2
                ControlConveyor(2,0);
                __delay_ms(1200);
                curAutoState = NextCube;
                break;
            case RunConv3:
                lcd_clear();
                lcd_out(1,1,"Run conveyor 3");
                ControlConveyor(3,0);
                curAutoState = WaitForSensorConv3Sensor;
                __delay_ms(300);
                break;
            case WaitForSensorConv3Sensor:
                lcd_clear();
                lcd_out(1,1,"Waiting for");
                lcd_out(2,1,"conv 3 sensor");
                WaitForSensor(conveyor3sensor);
                curAutoState = NextCube;
                __delay_ms(2000);
                break;
            case NextCube:
                ControlConveyor(5,0);
                curCube++;
                if (curCube == 5) {
                    curAutoState = End;
                    break;
                }
                lcd_clear();
                lcd_out(1,1,"Next cube is");
                sprintf(str, "%d", curCube); // Lets be fancy and use sprintf to construct a string
                lcd_out(2,1,str);
                curAutoState = PositionConv2StartPos;
                __delay_ms(1000);
                break;
            case End:
                break;
            default: // Handle any error in state handling
                lcd_clear();
                lcd_out(1,1,"Invalid state");
                lcd_out(2,1,"System halted");
                while(1);
         
        }
        
        if (curAutoState == End) {
            lcd_clear();
            lcd_out(1,1,"Finished");
            __delay_ms(1000);    
            break;
        }
        
    }
}

void runAutomaticState() {
    lcd_out(1,1, "Automatic       ");
    lcd_out(2,1, "                ");
    
    runAutomaticControl(); // Enter the state machine
    
    handleStateChange(Menu);
}

void SaveCubeDestination(short cubeNum){
    char str[17]; // Buffer for line for screen
    int keyVal = -1;
    
    lcd_clear();
    sprintf(str, "Dest for cube %d", cubeNum); // Lets be fancy and use sprintf to construct a string
    lcd_out(1,1,str);
    
    while(keyVal < 1 || keyVal > 3) {
        keyVal = readKeypad();
    }
    cubeData[cubeNum-1] = keyVal;
    
    lcd_clear();
    sprintf(str, "Cube %d to %d", cubeNum, keyVal);
    lcd_out(1,1,str);
    __delay_ms(300);
}