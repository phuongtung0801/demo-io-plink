



#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <FS.h>
#include <testOTA.h>

// config static IP
IPAddress local_IP(192, 168, 1, 33);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

//broker
const char *mqtt_server = "13.237.153.96";
const char *clientID = "esp32root";
const char *endTopic = "v1/device/LWT";
const char *deviceACK = "v1/demo/device/ACK";
const char *webCmdTopic = "v1/demo/web/cmd";
long int port = 1883;

//wifi
const char *ssid = "PLINK";
const char *password = "66668888";

//prototype
void mqttCallback(char *topic, uint8_t *payload, unsigned int length);


WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
  {
      Serial.println("STA failed to config");
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
      delay(1000);
      Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

  //connect MQTT broker
  mqttClient.setServer(mqtt_server, port);
  mqttClient.setCallback(mqttCallback);

  if (mqttClient.connect(
          clientID, endTopic, 1, true, "Sensor disconnected from mqtt"))
  {
      Serial.println("Connected to MQTT Broker!");
      mqttClient.publish(endTopic, "Sensor connected!", true);
  }
  else
  {
      Serial.println("Connection to MQTT Broker failed...");
  }
  if (!mqttClient.subscribe(webCmdTopic))
  {
   Serial.println("Failed to subscribe to ");
  }
    PyrOTA.initOTA();
}

void loop() {
  // put your main code here, to run repeatedly:
  mqttClient.loop();
  PyrOTA.loopOTA();
}


void mqttCallback(char *topic, uint8_t *payload, unsigned int length)
{
    String cmd = "";
    Serial.print("Message arrived [");
    Serial.print(topic);

    Serial.print("]: ");
    for (int i = 0; i < length; i++)
    {
        cmd += (char)payload[i];
    }
    DynamicJsonDocument jsonBuffer(1024);
    JsonObject msg = jsonBuffer.to<JsonObject>();
    msg["topic"] = topic;
    msg["msg"] = cmd;
    msg["type"] = "subscribe";
    String str;
    serializeJson(msg, str);
    Serial.println(str);
    /*Check cmd from client and execute appropriate I/O*/
    /*
    code something here
    */

    /*Finished cmd, send ACK back to client*/
    DynamicJsonDocument jsonBufferACK(1024);
    JsonObject msgACK = jsonBufferACK.to<JsonObject>();
    //status of each string
    msgACK["output"] = true; //relay button
    msgACK["input_relay"] = true;
    msgACK["input_emergency"] = true; //emergency button

    String strACK;
    serializeJson(msgACK, strACK);
    mqttClient.publish(deviceACK, strACK.c_str());
}