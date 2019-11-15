/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "pmvanker"
#define WLAN_PASS       "freewifi"

uint8_t LED_Pin1 = D0;
uint8_t LED_Pin2 = D1;

uint8_t LED_Pin1_S = 0;
uint8_t LED_Pin2_S = 0;


/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "postman.cloudmqtt.com"
#define AIO_SERVERPORT  17736                   // use 8883 for SSL
#define AIO_USERNAME    "oqpqdwuo"
#define AIO_KEY         "hZ3dEfrfFbsN"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish led1p = Adafruit_MQTT_Publish(&mqtt, "led1");
Adafruit_MQTT_Publish led2p = Adafruit_MQTT_Publish(&mqtt, "led2");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe led1s = Adafruit_MQTT_Subscribe(&mqtt, "led1");
Adafruit_MQTT_Subscribe led2s = Adafruit_MQTT_Subscribe(&mqtt, "led2");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  pinMode(LED_Pin1, OUTPUT);
  pinMode(LED_Pin2, OUTPUT);
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

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
  mqtt.subscribe(&led1s);
  mqtt.subscribe(&led2s);
}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &led1s) {
      Serial.print(F("Got: "));
      if(strcmp((const char*)led1s.lastread,"1")==0)
      {
        digitalWrite(LED_Pin1,HIGH);
        LED_Pin1_S = HIGH;
      }
      else if(strcmp((const char*)led1s.lastread,"0")==0)
      {
        digitalWrite(LED_Pin1,LOW);
        LED_Pin1_S = LOW;
      }
      Serial.println((char *)led1s.lastread);
    }
    else if (subscription == &led2s) {
      Serial.print(F("Got: "));
      if(strcmp((const char*)led2s.lastread,"1")==0)
      {
        digitalWrite(LED_Pin2,HIGH);
        LED_Pin2_S = HIGH;
      }
      else if(strcmp((const char*)led2s.lastread,"0")==0)
      {
        digitalWrite(LED_Pin2,LOW);
        LED_Pin2_S = LOW;
      }
      Serial.println((char *)led2s.lastread);
    }
  } 

  // Now we can publish stuff!
  Serial.print(F("\nSending Led Data "));
  Serial.print("...");
  if (! led1p.publish(LED_Pin1_S)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  if (! led2p.publish(LED_Pin2_S)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
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
