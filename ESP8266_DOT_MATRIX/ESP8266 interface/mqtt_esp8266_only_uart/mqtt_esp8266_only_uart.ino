/*
 * Load this into ESP8266
 */
#include <ESP8266WiFi.h>
//#include <SoftwareSerial.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/*
 * Software serial
 */
//SoftwareSerial mySerial(2, 3); // pin2=RX, pin3=TX 

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "LOTUS"
#define WLAN_PASS       "iamlotus"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "postman.cloudmqtt.com"
#define AIO_SERVERPORT  17736                   // use 8883 for SSL
#define AIO_USERNAME    "oqpqdwuo"
#define AIO_KEY         "xxxxxxxxxxx"

/************ Global State (you don't need to change this!) ******************/

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/
Adafruit_MQTT_Subscribe msg_sub = Adafruit_MQTT_Subscribe(&mqtt, "msg");

/*************************** Sketch Code ************************************/
void MQTT_connect();

void setup() {
  Serial.begin(115200);
//  mySerial.begin(115200);
  
  delay(10);
  Serial.println(F("Lotus IOT LED-MATRIX "));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&msg_sub);
}

void loop() {
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) 
  {
    if (subscription == &msg_sub) {
     Serial.println((char *)msg_sub.lastread);
    }
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
