// #include <ax12.h>
// #include <BioloidController.h>
// #include "poses.h"
//
//
// BioloidController bioloid = BioloidController(1000000);
//
// const int SERVOCOUNT = 2;
// int id;
// int pos;
// boolean IDCheck;
// boolean RunCheck;
//
// void MenuOptions();
//
// void RelaxServos();
//
// void MoveTest();
//
// void MoveCenter();
//
// void LEDTest();
//
// void ScanServo();
//
// void test();
//
// void setup() {
//     pinMode(0,OUTPUT);
//
//     //initialize variables
//     id = 1;
//     pos = 0;
//     IDCheck = 1;
//     RunCheck = 0;
//     //open serial port
//     Serial.begin(9600);
//     delay(500);
//     Serial.println("###########################");
//     Serial.println("Serial Communication Established.");
//
//     test();
//
//     // //Check Lipo Battery Voltage
//     //
//     // MoveCenter();
//     //
//     // //Scan Servos, return position.
//     // ScanServo();
//     //
//     // MoveTest();
//     //
//     //
//     // MenuOptions();
//
//     RunCheck = 1;
// }
//
// void test() {
//     id = 1;
//     Serial.println("###########################");
//     Serial.println("Starting Servo Scanning Test.");
//     Serial.println("###########################");
//     id = 1;
//     pos = ax12GetRegister(id);
//     Serial.print("Servo ID: ");
//     Serial.println(id);
//     Serial.print("Servo Position: ");
//     Serial.println(pos);
//
//     if (pos <= 0) {
//         Serial.println("###########################");
//         Serial.print("ERROR! Servo ID: ");
//         Serial.print(id);
//         Serial.println(" not found. Please check connection and verify correct ID is set.");
//         Serial.println("###########################");
//         IDCheck = 0;
//     }
//
//     id = (id++) % SERVOCOUNT;
//     delay(1000);
//
//     if (IDCheck == 0) {
//         Serial.println("###########################");
//         Serial.println(
//             "ERROR! Servo ID(s) are missing from Scan. Please check connection and verify correct ID is set.");
//         Serial.println("###########################");
//     } else {
//         Serial.println("All servo IDs present.");
//     }
//     if (RunCheck == 1) {
//         MenuOptions();
//     }
// }
//
//
// void loop() {
//     // read the sensor:
//
//     int inByte = Serial.read();
//
//     switch (inByte) {
//         case '1':
//             ScanServo();
//             break;
//
//         case '2':
//             MoveCenter();
//             break;
//
//         case '3':
//             RelaxServos();
//             break;
//
//         case '4':
//             MoveCenter();
//             MoveTest();
//             break;
//
//         case '6':
//             LEDTest();
//             break;
//     }
// }
//
//
// void ScanServo() {
//     id = 1;
//     Serial.println("###########################");
//     Serial.println("Starting Servo Scanning Test.");
//     Serial.println("###########################");
//
//     Serial.print(GetPosition(id));
//
//     while (id <= SERVOCOUNT) {
//         // pos = ax12GetRegister(id, 36, 2);
//         Serial.print("Servo ID: ");
//         Serial.println(id);
//         Serial.print("Servo Position: ");
//         Serial.println(pos);
//
//         if (pos <= 0) {
//             Serial.println("###########################");
//             Serial.print("ERROR! Servo ID: ");
//             Serial.print(id);
//             Serial.println(" not found. Please check connection and verify correct ID is set.");
//             Serial.println("###########################");
//             IDCheck = 0;
//         }
//
//         id = (id++) % SERVOCOUNT;
//         delay(1000);
//     }
//     if (IDCheck == 0) {
//         Serial.println("###########################");
//         Serial.println(
//             "ERROR! Servo ID(s) are missing from Scan. Please check connection and verify correct ID is set.");
//         Serial.println("###########################");
//     } else {
//         Serial.println("All servo IDs present.");
//     }
//     if (RunCheck == 1) {
//         MenuOptions();
//     }
// }
//
// void MoveCenter() {
//     delay(100); // recommended pause
//     bioloid.loadPose(Center); // load the pose from FLASH, into the nextPose buffer
//     bioloid.readPose(); // read in current servo positions to the curPose buffer
//     Serial.println("###########################");
//     Serial.println("Moving servos to centered position");
//     Serial.println("###########################");
//     delay(1000);
//     bioloid.interpolateSetup(1000); // setup for interpolation from current->next over 1/2 a second
//     while (bioloid.interpolating > 0) {
//         // do this while we have not reached our new pose
//         bioloid.interpolateStep(); // move servos, if necessary.
//         delay(3);
//     }
//     if (RunCheck == 1) {
//         MenuOptions();
//     }
// }
//
//
// void MoveTest() {
//     Serial.println("###########################");
//     Serial.println("Initializing Movement Sign Test");
//     Serial.println("###########################");
//     delay(500);
//     id = 1;
//     pos = 512;
//     while (id <= SERVOCOUNT) {
//         Serial.print("Moving Servo ID: ");
//         Serial.println(id);
//
//         while (pos >= 312) {
//             SetPosition(id, pos);
//             pos = pos--;
//             delay(10);
//         }
//
//         while (pos <= 512) {
//             SetPosition(id, pos);
//             pos = pos++;
//             delay(10);
//         }
//
//         //iterate to next servo ID
//         id = id++;
//     }
//     if (RunCheck == 1) {
//         MenuOptions();
//     }
// }
//
//
// void MenuOptions() {
//     Serial.println("###########################");
//     Serial.println("Please enter option 1-5 to run individual tests again.");
//     Serial.println("1) Servo Scanning Test");
//     Serial.println("2) Move Servos to Center");
//     Serial.println("3) Relax Servos");
//     Serial.println("4) Perform Movement Sign Test");
//     Serial.println("5) Check System Voltage");
//     Serial.println("6) Perform LED Test");
//     Serial.println("###########################");
// }
//
// void RelaxServos() {
//     id = 1;
//     Serial.println("###########################");
//     Serial.println("Relaxing Servos.");
//     Serial.println("###########################");
//     while (id <= SERVOCOUNT) {
//         Relax(id);
//         id = (id++) % SERVOCOUNT;
//         delay(50);
//     }
//     if (RunCheck == 1) {
//         MenuOptions();
//     }
// }
//
// void LEDTest() {
//     id = 1;
//     Serial.println("###########################");
//     Serial.println("Running LED Test");
//     Serial.println("###########################");
//     while (id <= SERVOCOUNT) {
//         ax12SetRegister(id, 25, 1);
//         Serial.print("LED ON - Servo ID: ");
//         Serial.println(id);
//         delay(3000);
//         ax12SetRegister(id, 25, 0);
//         Serial.print("LED OFF - Servo ID: ");
//         Serial.println(id);
//         delay(3000);
//         id = id++;
//     }
//
//     if (RunCheck == 1) {
//         MenuOptions();
//     }
// }


/***************************
* AXSimpleTest
 * This sketch sends positional commands to the AX servo
 * attached to it - the servo must set to ID # 1
 * The sketch will send a value, i, to the servo.
 * 'For' loops are used to increment and decrement the value of 'i'
 ***************************/

//import ax12 library to send DYNAMIXEL commands
#include <ax12.h>
#include <BioloidController.h>

volatile unsigned long pwm_1_length = 0;
volatile unsigned long pwm_2_length = 0;

BioloidController controller;
int id1;
int id2;

int pin = 0;

void setup() {
    Serial.begin(9600);
    delay(500);
    Serial.println("Starting AXSimpleTest");

    delay(500);
    controller.setup(2); // setup the controller with 2 servos
    delay(500);
    // id1 = controller.getId(0);
    // id2 = controller.getId(1);

    Serial.printf("id1: %d :: id2: %d", id1, id2);
    pinMode(0, INPUT);
    id1 = 1;
    id2 = 2;


    // SetPosition(2, 0); //set the position of servo # 1 to '0'
    // SetPosition(1, 0);
    // delay(100); //wait for servo to move
    //
    // pinMode(A6,INPUT);
    // pinMode(A7,INPUT);
}

void loop() {

    unsigned long highTime = pulseIn(pin, HIGH);
    // unsigned long lowTime = pulseIn(pin, LOW);
    unsigned long period = 10000 / 5; // 5 Hz = 200 ms period


    Serial.printf("highTime: %d lowTime: %d period: %d\n", highTime, highTime, period);

    float dutyCycle = (highTime / period);
    Serial.print("Duty Cycle: ");
    Serial.print(dutyCycle);
    Serial.println("%");
    Serial.printf("");

    // map the desired position to the range of the servo
    int desiredPosition = map(dutyCycle, 0, 100, 0, 1023); // Assuming the servo range is 0-1023

    Serial.println(desiredPosition);
    SetPosition(1, desiredPosition);
    SetPosition(2, desiredPosition);
    // controller.setId(1, 1);
    // controller.setId(0, 0);


    // int pwm_value = digitalRead(pin);
    //
    // Serial.println(pwm_value);

    // delay(500);


    // for (int i = 0; i < 1023; i++) {
    //     Serial.println("loop");
    //     SetPosition(id1, i);
    //     SetPosition(id2, i);
    //     delay(2);
    // }


    // pwm_1_length = pulseIn(A6, HIGH); //read the value of the PWM signal
    //
    // pwm_2_length = pulseIn(A7, LOW); //read the value of the potentiometer
    //
    // Serial.print(" Pos 1: ");
    //
    // Serial.println(GetPosition(1));
    // Serial.print(" Pos 2: ");
    //
    // Serial.println(GetPosition(0));


    // pwm length to position conversion
    // int pos_1 = map(pwm_1_length, 1000, 2000, 0, 1023); //map the value of the PWM signal to a position
    // int pos_2 = map(pwm_2_length, 1000, 2000, 0, 1023); //map the value of the potentiometer to a position

    // SetPosition(1, pos_1);
    // SetPosition(2, pos_2);

}
