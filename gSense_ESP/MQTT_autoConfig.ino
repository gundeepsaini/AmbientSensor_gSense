

/******************** LIB **************************************/
#define MQTT_MAX_PACKET_SIZE 1024  // < ----- Change in lib: This is because the defaul maxium length is 128b. So just go to PubSubClient.h and change #define MQTT_MAX_PACKET_SIZE 128 to #define MQTT_MAX_PACKET_SIZE 1024
#include "src/PubSubClient/PubSubClient.h"
#include <ArduinoJson.h>


/********************* Var *************************************/
WiFiClient espClient;
PubSubClient client(espClient);

long lastReconnectAttempt = 0;
float lastTemp, lastHumidity, lastLight, lastPressure;

/******************** Config **************************************/
const char* mqtt_server 	  = SECRET_MQTT_Server;
const char* mqtt_user 		  = SECRET_MQTT_User;
const char* mqtt_password 	= SECRET_MQTT_Pass;


#define MQTT_CONFIG_TEMP      "homeassistant/sensor/gSense/Temp/config"
#define MQTT_CONFIG_HUMIDITY  "homeassistant/sensor/gSense/Humidity/config"
#define MQTT_CONFIG_LIGHT     "homeassistant/sensor/gSense/Light/config"
#define MQTT_CONFIG_PRESSURE  "homeassistant/sensor/gSense/Pressure/config"
#define MQTT_CONFIG_NOISE     "homeassistant/sensor/gSense/Noise/config"
#define MQTT_CONFIG_PPM       "homeassistant/sensor/gSense/PPM/config"

#define MQTT_TOPIC_STATE      "homeassistant/sensor/gSense/state"


/**************** External Functions ************************************/

void MQTT_config()
{
	client.setServer(mqtt_server, SECRET_MQTT_Port);
 	client.setCallback(MQTT_MessageRecd_callback);
}


void MQTT_loop()
{
	if (!client.connected())
    	MQTT_reconnect();              
  
  	client.loop();
}


void MQTT_publish()
{   
    //float diff = 0.1;
    //bool TempChanged      = MQTT_hasValueChanged(Temperature, lastTemp, diff);
    //bool HumidityChanged  = MQTT_hasValueChanged(Humidity, lastHumidity, diff);
    //bool PressureChanged  = MQTT_hasValueChanged(Pressure, lastPressure, diff);
    //bool LightChanged     = MQTT_hasValueChanged(lux, lastLight, diff);


    if(1)//TempChanged || HumidityChanged || PressureChanged || LightChanged )
    {
      // Use arduinojson.org/v6/assistant to compute the capacity.
      const size_t capacity = JSON_OBJECT_SIZE(9);
      DynamicJsonDocument doc(capacity);
      
      doc["temperature"] = String(Temperature);
      doc["humidity"] = String(int(Humidity));
      doc["light"] = String(lux);
      doc["pressure"] = String(Pressure);
      doc["noise"] = String(Noise);
      doc["PPM"] = String(PPM_LPG);
            
      lastTemp = Temperature;
      lastHumidity = Humidity;
      lastLight = lux;
      lastPressure = Pressure;

      char data[256];
      serializeJson(doc, data, sizeof(data));
      client.publish(MQTT_TOPIC_STATE, data, true);
      //Serial.println(data);
    }
    else
      Serial.println("Value change not material");
}


/**************** Internal Functions ************************************/

void MQTT_reconnect() 
{
  if (millis()/1000 - lastReconnectAttempt > 30 || lastReconnectAttempt == 0) 
  {
      Serial.println("MQTT reconnecting");
      if (client.connect(DeviceHostName, mqtt_user, mqtt_password)) 
      {
        //MQTT_publish_config_Temp();
        //MQTT_publish_config_Humidity();
        //MQTT_publish_config_Light();
        //MQTT_publish_config_Pressure();
        //MQTT_publish_config_Noise();
        //MQTT_publish_config_PPM();

        Serial.println("MQTT connected");
      }
      lastReconnectAttempt = millis()/1000;
  }
}




void MQTT_MessageRecd_callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) 
    Serial.print((char)payload[i]);
  Serial.println();
}



void MQTT_publish_config_Temp() 
{
  // Use arduinojson.org/v6/assistant to compute the capacity.
  const int capacity = JSON_OBJECT_SIZE(7); //  <-------- Change it as reqd
  StaticJsonDocument<capacity> root;  

  root["dev_cla"] = "temperature";
  root["name"] = "gSense Temp";
  root["stat_t"] = MQTT_TOPIC_STATE;
  root["unit_of_meas"] = "°C";
  root["val_tpl"] = "{{value_json.temperature}}";
  root["pl_avail"] = "online";
  root["pl_not_avail"] = "offline";
  
  char message[256];
  serializeJson(root, message,sizeof(message));
  client.publish(MQTT_CONFIG_TEMP, message, true);
  //Serial.println(message);
}


void MQTT_publish_config_Humidity() 
{
  // Use arduinojson.org/v6/assistant to compute the capacity.
  const int capacity = JSON_OBJECT_SIZE(7); //  <-------- Change it as reqd
  StaticJsonDocument<capacity> root;  

  root["dev_cla"] = "humidity";
  root["name"] = "gSense Humidity";
  root["stat_t"] = MQTT_TOPIC_STATE;
  root["unit_of_meas"] = "%";
  root["val_tpl"] = "{{value_json.humidity}}";
  root["pl_avail"] = "online";
  root["pl_not_avail"] = "offline";
  
  char message[256];
  serializeJson(root, message,sizeof(message));
  client.publish(MQTT_CONFIG_HUMIDITY, message, true);
  //Serial.println(message);
}


void MQTT_publish_config_Light() 
{
  // Use arduinojson.org/v6/assistant to compute the capacity.
  const int capacity = JSON_OBJECT_SIZE(7); //  <-------- Change it as reqd
  StaticJsonDocument<capacity> root;  

  root["dev_cla"] = "illuminance";
  root["name"] = "gSense Light";
  root["stat_t"] = MQTT_TOPIC_STATE;
  root["unit_of_meas"] = "lx";
  root["val_tpl"] = "{{value_json.light}}";
  root["pl_avail"] = "online";
  root["pl_not_avail"] = "offline";
  
  char message[256];
  serializeJson(root, message,sizeof(message));
  client.publish(MQTT_CONFIG_LIGHT, message, true);
  //Serial.println(message);
}


void MQTT_publish_config_Pressure() 
{
  // Use arduinojson.org/v6/assistant to compute the capacity.
  const int capacity = JSON_OBJECT_SIZE(7); //  <-------- Change it as reqd
  StaticJsonDocument<capacity> root;  

  root["dev_cla"] = "pressure";
  root["name"] = "gSense Pressure";
  root["stat_t"] = MQTT_TOPIC_STATE;
  root["unit_of_meas"] = "mbar";
  root["val_tpl"] = "{{value_json.pressure}}";
  root["pl_avail"] = "online";
  root["pl_not_avail"] = "offline";
  
  char message[256];
  serializeJson(root, message,sizeof(message));
  client.publish(MQTT_CONFIG_PRESSURE, message, true);
  //Serial.println(message);
}

void MQTT_publish_config_Noise() 
{
  // Use arduinojson.org/v6/assistant to compute the capacity.
  const int capacity = JSON_OBJECT_SIZE(7); //  <-------- Change it as reqd
  StaticJsonDocument<capacity> root;  

  root["dev_cla"] = "signal_strength";
  root["name"] = "gSense Noise";
  root["stat_t"] = MQTT_TOPIC_STATE;
  root["unit_of_meas"] = "dB";
  root["val_tpl"] = "{{value_json.noise}}";
  root["pl_avail"] = "online";
  root["pl_not_avail"] = "offline";
  
  char message[256];
  serializeJson(root, message,sizeof(message));
  client.publish(MQTT_CONFIG_NOISE, message, true);
  //Serial.println(message);
}

void MQTT_publish_config_PPM() 
{
  // Use arduinojson.org/v6/assistant to compute the capacity.
  const int capacity = JSON_OBJECT_SIZE(7); //  <-------- Change it as reqd
  StaticJsonDocument<capacity> root;  

  root["name"] = "gSense PPM";
  root["stat_t"] = MQTT_TOPIC_STATE;
  root["unit_of_meas"] = "ppm";
  root["val_tpl"] = "{{value_json.PPM}}";
  root["pl_avail"] = "online";
  root["pl_not_avail"] = "offline";
  
  char message[256];
  serializeJson(root, message,sizeof(message));
  client.publish(MQTT_CONFIG_PPM, message, true);
  //Serial.println(message);
}

bool MQTT_hasValueChanged(float newValue, float prevValue, float maxDiff) 
{
  return !isnan(newValue) && (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}
