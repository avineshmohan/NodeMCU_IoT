#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char ssid[] = "HARI";
const char password[] = "123456789";

ESP8266WebServer server(80);

#define pin D4

void setup()
{

pinMode(D4,OUTPUT);
Serial.begin(115200);
WiFi.softAP(ssid, password);
IPAddress myIP = WiFi.softAPIP();
Serial.print("AP IP address: ");
Serial.println(myIP);
server.begin();
server.on("/led", led);

}

void loop() {
  server.handleClient();
}

void led() {
 String myhtml="<!DOCTYPE html><html><body><h2>The button Element</h2><form><button type=\"submit\" name=\"pin\" value=\"0\">LED ON </button><button type=\"submit\" name=\"pin\" value=\"1\">LED OFF </button></form></body></html>";
 server.send(200, "text/html",myhtml);
 if (server.arg("pin")=="1")
{
 digitalWrite(D4,HIGH);
}
else
{
 digitalWrite(D4,LOW);
}

}
