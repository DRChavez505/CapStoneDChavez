/*
 * Project CapStoneDChavez
 * Description: weather Chamber
 * Author:Dan Chavez
 * Date: 4.19.2023
 */
#include "IoTClassroom_CNM.h"
#include <math.h>
<<<<<<< HEAD
#include "Stepper.h"
=======
>>>>>>> 831eeabd64d1d4f55aacc9d11d161a611f596330
#include "particle.h"
#include "Adafruit_BME280.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
<<<<<<< HEAD
Stepper myStepper(2048, D8, D7, D6, D5);
=======
>>>>>>> 831eeabd64d1d4f55aacc9d11d161a611f596330
Adafruit_SSD1306 display(D3);
Adafruit_BME280 bme;
int rot=2;
bool status;
float tempC; 
float pressPA;
float humidRH;
const int D=2;
<<<<<<< HEAD
Button testButton (D4); 
// relay stuff
const int relayPin=D5;
int relayOn;
int relayOff;
=======
Button testButton (D3); 
// relay stuff
const int relayPin=D5;
>>>>>>> 831eeabd64d1d4f55aacc9d11d161a611f596330
bool RelayState;
bool offOn=1;
bool onOff=0;
// setup() runs once, when the device is first turned on.

void setup() {
<<<<<<< HEAD
  Serial.begin(9600);//initialize the serial port first
  Wire.begin();//start the I2c
  Wire.beginTransmission(0x68); 
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //start the display
=======
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
>>>>>>> 831eeabd64d1d4f55aacc9d11d161a611f596330
  display.setRotation(rot);
  display.display(); 
  delay(1000);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
<<<<<<< HEAD
  display.clearDisplay(); 
  myStepper.setSpeed(5); //motor speed setting
=======
  display.clearDisplay();
>>>>>>> 831eeabd64d1d4f55aacc9d11d161a611f596330
  pinMode(relayPin, OUTPUT);
  Serial.printf("Basic test:");
  waitFor(Serial.isConnected,15000);
  WiFi.on();
  WiFi.setCredentials("IoTNetwork");
  WiFi.connect();
  while(WiFi.connecting());
 }
<<<<<<< HEAD
=======

>>>>>>> 831eeabd64d1d4f55aacc9d11d161a611f596330
void loop() {
    status = bme.begin(0x76);
    if (status == false)
    {
      Serial.printf("BME280 at address 0x%02X failed to start", 0x76);
      }
      tempC = bme.readTemperature(); //deg C
      pressPA = bme.readPressure();  //pascals
      humidRH = bme.readHumidity (); // %RH
<<<<<<< HEAD
      Serial.printf("Temp %0.1f\nHumidity %0.1f\nPressure %f0.1", tempC, humidRH, pressPA);
=======
>>>>>>> 831eeabd64d1d4f55aacc9d11d161a611f596330
      display.printf("Temp %0.1f\nHumidity %0.1f\nPressure %f0.1", tempC, humidRH, pressPA);
      display.display();
      delay(1000);
      display.display();
<<<<<<< HEAD
   if(BUTTON1_PRESSED){
    turnRelayOn();
    delay(5000);
    myStepper.step(2048);
    delay(500);
    Serial.printf("button is pressed\n");
  }
  else{
    turnRelayOff();
    delay(5000);
    myStepper.step(-2048);
    delay(500);
    Serial.printf("Button is not pressed \n");
  }
}
void turnRelayOn(){
   Serial.printf("activating pump %i\n",relayPin);
   switchON(relayPin);
   digitalWrite(relayPin, offOn);
}

void turnRelayOff()  {
   digitalWrite(relayPin, onOff);
   Serial.printf("turning pump off %i\n",relayPin);
}
=======
  if(BUTTON1_PRESSED){
  void turnRelayOn();
    delay(5000);
    Serial.printf("button is pressed\n");
  }
  else{
   void turnRelayOff();
    delay(5000);
    Serial.printf("Button is not pressed \n");
  }
}
  void turnRelayOn(){
  Serial.printf("activating pump %i\n",relayPin);
  digitalWrite(relayPin, HIGH);
   
   switchON(relayPin);
   digitalWrite(relayPin, offOn);
}

void turnRelayOff()  {
   digitalWrite(relayPin, onOff);
   Serial.printf("turning pump off %i\n",relayPin);
}
>>>>>>> 831eeabd64d1d4f55aacc9d11d161a611f596330
