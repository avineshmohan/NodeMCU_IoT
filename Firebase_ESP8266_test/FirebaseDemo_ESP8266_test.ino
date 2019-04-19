#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "iottest-168d4.firebaseio.com"
#define FIREBASE_AUTH "l7n1nyvFUg4Cd4mw3IF1Bth0CkEsbrbMoqYXy9x3"
#define WIFI_SSID "BOLT"
#define WIFI_PASSWORD "FORGE958"

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
