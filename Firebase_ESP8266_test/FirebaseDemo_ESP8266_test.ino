#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "db_url"
#define FIREBASE_AUTH "db_secret"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PWD"

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  if(Firebase.getInt("led") == 1){
    digitalWrite(LED_BUILTIN,LOW);
    delay(4000);
  }
  else if(Firebase.getInt("led") == 0){
    digitalWrite(LED_BUILTIN,HIGH);
    delay(4000);
  }
}
