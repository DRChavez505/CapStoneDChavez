/*
 * Project CapStoneDChavez
 * Description: weather Chamber
 * Author:Dan Chavez
 * Date: 4.19.2023
 */
#include "IoTClassroom_CNM.h"
#include <math.h>
#include "particle.h"
#include "Adafruit_BME280.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
Adafruit_SSD1306 display(D3);
Adafruit_BME280 bme;
int rot=2;
bool status;
float tempC; 
float pressPA;
float humidRH;
const int D=2;
Button testButton (D6); 
// relay stuff
const int relayPin=D5;
int relayOn;
int relayOff;
bool RelayState;
bool offOn=1;
bool onOff=0;
// setup() runs once, when the device is first turned on.

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(rot);
  display.display(); 
  delay(1000);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
  display.clearDisplay();
   pinMode(relayPin, OUTPUT);
  Serial.printf("Basic test:");
  waitFor(Serial.isConnected,15000);
  WiFi.on();
  WiFi.setCredentials("IoTNetwork");
  WiFi.connect();
  while(WiFi.connecting());
 }

void loop() {
    status = bme.begin(0x76);
    if (status == false)
    {
      Serial.printf("BME280 at address 0x%02X failed to start", 0x76);
      }
      tempC = bme.readTemperature(); //deg C
      pressPA = bme.readPressure();  //pascals
      humidRH = bme.readHumidity (); // %RH
      display.printf("Temp %0.1f\nHumidity %0.1f\nPressure %f0.1", tempC, humidRH, pressPA);
      display.display();
      delay(1000);
      display.display();
  inputValue=digitalRead(D3);
  IF(BUTTON1_PRESSED){
    turnRelayOn();
    delay(5000);
    serial.printf("button is pressed\n")
  }
  else{
    turnRelayOff();
    delay(5000);
    Serial.printf("Button is not pressed \n")
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