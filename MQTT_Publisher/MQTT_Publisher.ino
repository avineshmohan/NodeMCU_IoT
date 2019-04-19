#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


#define WLAN_SSID       "ProtoSem"
#define WLAN_PASS       "123456789"



#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "avineshmohan"
#define AIO_KEY         "7e20319c5d5b4688bdd4f9d286056339"



WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Setup a feed called 'photocell' for publishing.

Adafruit_MQTT_Publish myFirstValue = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell");


void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  pinMode(A0,OUTPUT);

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
 
}


void loop() {

  MQTT_connect();

  

  // Now we can publish stuff!
  Serial.print(F("\nSending myValue "));
  Serial.print(senVal);
  Serial.print("...");
  if (! myFirstValue.publish(getVal())) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

 
  delay(1000);
}

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


//  get sensor Value

uint8_t getVal(){
senVal = analogRead(A0);

return senVal;
  
}
