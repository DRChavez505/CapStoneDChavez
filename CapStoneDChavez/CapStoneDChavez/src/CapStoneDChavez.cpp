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
#include "_BUTTON_H_"
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
bool offOn();
bool onOff();
#line 21 "c:/Users/daniu/Documents/iot/CapStoneDChavez/CapStoneDChavez/CapStoneDChavez/src/CapStoneDChavez.ino"
TCPClient TheClient; 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 
Adafruit_MQTT_Publish relayPosition = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/relayState");
Adafruit_MQTT_Subscribe buttonOnOff = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/buttonOnOff");
unsigned int lastTime, last;
const int LEDPIN = D7;
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
void MQTT_connect();
bool MQTT_ping();
Button BUTTON_PRESSED (D3); 

void setup() {
Serial.begin(9600);
waitFor(Serial.isConnected,15000);
WiFi.on(); //wifi stuff
WiFi.connect();
while(WiFi.connecting());
{
Serial.printf(".");
}
  Serial.printf("\n\n");
  mqtt.connect();//Setup MQTT subscription
  mqtt.subscribe(&buttonOnOff);
    bme.begin(0x76);
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //OLED Setup
      display.setRotation(rot);
      display.clearDisplay();
      delay(1000);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.display();
              myStepper.setSpeed(5); //motor speed setting
              pinMode(relayPin, OUTPUT);
                Serial.printf("Basic test:");
  }

void loop() {
MQTT_connect();
MQTT_ping();
// this is our 'wait for incoming subscription packets' busy subloop 
  Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(100))) {
      if (subscription == &buttonOnOff) {
        subValue = atof((char *)buttonOnOff.lastread);
        Serial.printf("%f\n",subValue);
    }
  }
      if(subValue == 1){
        digitalWrite(D7, HIGH);
        }
      if(subValue == 0){
            digitalWrite(D7, LOW);
        }
    humidRH = bme.readHumidity();   // Read the humidity from the BME280 sensor.
    if (humidRH >= 28) {  // Check if the humidity is greater than or equal to 28%.
        myStepper.step(2048);  // drive the stepper motor.
        digitalWrite(relayPin, HIGH);   // relay pump on
        } else {   // reverse stepper motor.
            myStepper.step(-2048);   // relaypump off.
            digitalWrite(relayPin, LOW);
  }
      Serial.printf("BME280 at address 0x%02X failed to start", 0x76);
      tempC = bme.readTemperature(); //deg C
      humidRH = bme.readHumidity (); // %RH

      Serial.printf("Temp %0.1f\nHumidity %0.1f\n", tempC, humidRH);
      display.printf("Temp %0.1f\nHumidity %0.1f\n", tempC, humidRH);
      display.display();
      delay(1000);
      display.display();  

if(BUTTON_PRESSED){
  offOn();
    delay(5000);
    Serial.printf("button is pressed\n");
  }
  else{
  onOff();
    delay(5000);
    Serial.printf("Button is not pressed \n");
  }
}
bool MQTT_ping() {
  static unsigned int last;
  bool pingStatus;

  if ((millis()-last)>1200000) {
      Serial.printf("Pinging MQTT \n");
      pingStatus = mqtt.ping();
      if(!pingStatus) {
        Serial.printf("Disconnecting \n");
        mqtt.disconnect();
      }
      last = millis();
  }
  return pingStatus;
  }

bool offOn(){
   Serial.printf("activating pump %i\n",relayPin);
     digitalWrite(relayPin, off_On);
}
bool onOff(){
   digitalWrite(relayPin, on_Off);
   Serial.printf("turning pump off %i\n",relayPin);
}
  
  void MQTT_connect(){
  int8_t ret;

   // Return if already connected.
  if (mqtt.connected()) {
    return;
  }
  
   Serial.print("Connecting to MQTT... ");
   while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.printf("Error Code %s\n",mqtt.connectErrorString(ret));
       Serial.printf("Retrying MQTT connection in 5 seconds...\n");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds and try again
  }
  Serial.printf("MQTT Connected!\n");}