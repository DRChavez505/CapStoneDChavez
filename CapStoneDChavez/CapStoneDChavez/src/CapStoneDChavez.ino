/*
 * Project CapStoneDChavez
 * Description: Weather Chamber
 * Author:Dan Chavez
 * Date:4.19.2023
 */

// setup() runs once, when the device is first turned on.
#include "math.h"
#include "Stepper.h"
Stepper myStepper(2048, D8, D7, D6, D5);
void setup() {
myStepper.setSpeed(15);
Wire.begin();
Wire.beginTransmission(0x68);
Wire.write(0x6B);
Wire.write(0x00);
Wire.endTransmission(true);
// Put initialization like pinMode and begin functions here.
}
// loop() runs over and over again, as quickly as it can execute.
void loop() {
myStepper.step(4096);
delay(500);
myStepper.step(-2048);
delay(500);
}
// The core of your code will likely live here.