/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/daniu/Documents/iot/CapStoneDChavez/CapStoneDChavez/CapStoneDChavez/src/CapStoneDChavez.ino"
/*
 * Project CapStoneDChavez
 * Description: weather Chamber
 * Author:Dan Chavez
 * Date: 4.19.2023
 */

#include "particle.h"
#include <math.h>
#include "stepper.h"
#include "Adafruit_BME280.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "credentials.h"
#include "JsonParserGeneratorRK.h"
// Declare global variables here
void setup();
void loop();
#line 20 "c:/Users/daniu/Documents/iot/CapStoneDChavez/CapStoneDChavez/CapStoneDChavez/src/CapStoneDChavez.ino"
TCPClient TheClient; 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 
Adafruit_MQTT_Publish relayPosition = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/relayState");
Adafruit_MQTT_Subscribe buttonOnOff = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/buttonOnOff");

unsigned int lastTime, last;
const int LEDPIN = D7;
unsigned long currentTime;
unsigned long relayStartTime;
unsigned long relayDuration = 240000; //4 minutes for demo 40 minutes would work better.
float subValue,pubValue;

Stepper myStepper(2048, D8, D7, D6, D5);

Adafruit_SSD1306 display(D3);
int rot=0;

Adafruit_BME280 bme;
bool status;
float tempC; 
float humidRH;

const int D=2;
const int relayPin=D12;
bool relayState;
bool off_On=1;
bool on_Off=0;

void MQTT_connect(); //connecting to broker
bool MQTT_ping();

class Button; //declaring a class for this button
int BUTTON_PRESSED(D3); 

void setup() {
Serial.begin(9600); //starting serial connection
waitFor(Serial.isConnected,15000); //wait for connection
WiFi.on(); //wifi stuff
WiFi.connect();
bme.begin(0x76); //starting BME 
while(WiFi.connecting());
{
Serial.printf(".");
}
  Serial.printf("\n\n");

  mqtt.connect();//Setup MQTT broker
  mqtt.subscribe(&buttonOnOff); //buttonOnOff at adafruit.io
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //OLED Setup
      display.setRotation(rot);
      display.clearDisplay();
      delay(1000);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.display();
        
        myStepper.setSpeed(5); //initializing the Stepper & motor speed setting
            pinMode(relayPin, OUTPUT); //intitialize the relay switch
              pinMode(D3, INPUT); // Initialize the physical button

                Serial.printf("Basic test:");
                currentTime = millis();
  }

void loop() {
  // Get the current time.
  unsigned long currentTime = millis();

  // Read the humidity from the BME280 sensor.
  float humidRH = bme.readHumidity();
  float tempC; 

  // Check if the humidity is below 28%.
  if (humidRH < 28) {
    // Close the door and turn on the relay.
    myStepper.step(-1024);
    digitalWrite(relayPin, HIGH);
    Serial.printf("Humidity too low Closing Door and Starting Relay/Pump\n");
    display.printf("Humidity too low Closing Door and Starting Relay/Pump\n");
  } else {
    // Turn the relay off and open the door.
    digitalWrite(relayPin, LOW);
    myStepper.step(1024);
    Serial.printf("Humidity is above 28%. Stopping Relay/Pump and Opening Door\n");
    display.printf("Humidity is above 28%. Stopping Relay/Pump and Opening Door\n");
  }

  // Check the value of the buttonOnOff feed on Adafruit.io.
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(100))) {
    if (subscription == &buttonOnOff) {
      // Read the value of the feed.
      bool value = atof((char *)buttonOnOff.lastread);

      // Set the physical button to the same state.
      digitalWrite(D3, value);

      // Check if the button is pressed.
      if (value == true) {
        // Close the door and turn on the pump.
        myStepper.step(-1024);
        digitalWrite(relayPin, HIGH);
      } else {
        // Turn the relay off and open the door.
        digitalWrite(relayPin, LOW);
        myStepper.step(1024);
      }
    }
  }
}