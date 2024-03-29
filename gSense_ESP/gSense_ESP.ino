/*-----------------------------------------

            gSense

Date: July 2014 (v00)
Device: ESP8266 NodeMcU  <--->  Atmega328

Block Diagram / Circuit Diagram: OneNote Workbook

Note:
  - Reset ESP after upload, disable IPv6, 
      reset adapter, allow port in firewall
  - send "OTA" on blynk terminal to enter dedicated mode
    or navigate to "ip/OTA" for OTA through web portal
  

------------------------------------------- */

/* ------------- LIB ------------------------------ */



#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <Wire.h>

#include "Secrets.h"
#include "src/DHTesp/DHTesp.h"
#include "src/BH1750/BH1750.h"

#include "SFE_BMP180.h"
#include <BlynkSimpleEsp8266.h>
#include <DS18B20.h>



/* ------------- CONFIG VAR ------------------------------ */
//#define SERIALCOM true
#define TempSensorPin 13
#define DHTPin   4

unsigned long looptime_Fast     = 0;    // in secs
unsigned long looptime_Mid1     = 5;    // in secs
unsigned long looptime_Mid2     = 10;   // in secs
unsigned long looptime_Slow 		  = 1 * (60);   	 // in mins
unsigned long looptime_VerySlow 	= 15 *(60);      // in mins
const long utcOffsetInSeconds     = 1 * (60*60);   // in hours
unsigned long NTP_Update_Period   = 6 * (60*60);   // in hours



/* ------------- VAR ------------------------------ */
const char* ssid 		         = SECRET_WIFI_SSID3;
const char* pass 		         = SECRET_WIFI_PASS3;
const char* DeviceHostName   = SECRET_Device_Name2;
const char* OTA_Password 	   = SECRET_Device_OTA_PASS; 
unsigned long lastrun_fast, lastrun_Mid1;
unsigned long lastrun_Mid2, lastrun_slow, lastrun_Veryslow;
unsigned long lastrun_30mins,lastrun_OTA, LastNTP_Update;
bool OTA_Mode=0;
float Temperature,Humidity,Temperature_DHT11;
float Noise, PPM_LPG;
uint16_t lux;
double Pressure,Altitude,SeaLevel_Pressure = 1013.25; //mBar
String webpage ="";
String page="",data0="",data1="",data2="",data3="";

DS18B20 ds(TempSensorPin);
BH1750 LightMeter;
SFE_BMP180 BMP180;
DHTesp DHT;
ESP8266WebServer server(80);


/* ------------- Functions ------------------------------ */

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  Serial.println(DeviceHostName);

  wifi_station_set_hostname(DeviceHostName);
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    Serial.println("Wifi Error! Rebooting in 30s...");
    delay(30 *1000);
    ESP.restart();
    while(1);
  }
  
  Serial.print("Connected to ");
  Serial.print(WiFi.SSID());
  Serial.print(", IP:");
  Serial.println(WiFi.localIP());

  Wire.begin(14,12);
  Config_TempSensor_DS18B20();
  LightMeter.begin();
  DHT.setup(DHTPin, DHTesp::DHT11);
  BMP180.begin();
  Serial.println("Sensors Initialized");
  
  WebServer_Config();
  OTA_Config();
  //Blynk_Config();
  MQTT_config();
  Config_Time();

  digitalWrite(LED_BUILTIN, HIGH);
	Serial.println("Ready");
}


void loop() 
{
  // Always
  Always_loop();

  // Fast Loop
 if(!OTA_Mode && ((millis()/1000 - lastrun_fast > looptime_Fast) || lastrun_fast ==0))
  {
    lastrun_fast = millis()/1000;
    Fast_Loop();
  }

  // Mid1 Loop
 if(!OTA_Mode && ((millis()/1000 - lastrun_Mid1 > looptime_Mid1) || lastrun_Mid1 ==0))
  {
    lastrun_Mid1 = millis()/1000;
    Mid1_Loop();
  }

  // Mid2 Loop
 if(!OTA_Mode && ((millis()/1000 - lastrun_Mid2 > looptime_Mid2) || lastrun_Mid2 ==0))
  {
    lastrun_Mid2 = millis()/1000;
    Mid2_Loop();
  }

  // Slow Loop
 if(!OTA_Mode && ((millis()/1000 - lastrun_slow > looptime_Slow) || lastrun_slow ==0))
  {
    lastrun_slow = millis()/1000;
    Slow_Loop();
  }

    // Very Slow Loop
 if(!OTA_Mode && ((millis()/1000 - lastrun_Veryslow > looptime_VerySlow) || lastrun_Veryslow ==0))
  {
    lastrun_Veryslow = millis()/1000;
    VerySlow_Loop();
  }
}
