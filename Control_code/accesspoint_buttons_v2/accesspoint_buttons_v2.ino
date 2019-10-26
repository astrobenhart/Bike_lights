#include <ESP8266WiFi.h>

// constants
WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);
byte ledPin = 2;
int leftbutton = 5;
int rightbutton = 4;

// variables
String state = "";
int leftbuttonstate = 0;
int rightbuttonstate = 0;

void setup() {
 Serial.begin(9600);
 WiFi.mode(WIFI_AP);
 WiFi.softAP("ESP_access", "andr0m3da");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
 pinMode(ledPin, OUTPUT);
 Serial.println();
 Serial.println("Server started.");
 Serial.print("IP: "); Serial.println(WiFi.softAPIP());
 Serial.print("MAC:"); Serial.println(WiFi.softAPmacAddress());
 pinMode(leftbutton, INPUT);
 pinMode(rightbutton, INPUT);
}

void loop() {
  leftbuttonstate = digitalRead(leftbutton);
  rightbuttonstate = digitalRead(rightbutton);

  if ((leftbuttonstate == HIGH) && (rightbuttonstate == LOW)) {
    WiFiClient client = server.available();
    if (!client) {return;}
    digitalWrite(ledPin, LOW);
    client.println("l\r");
    client.flush();
  } else if ((leftbuttonstate == LOW) && (rightbuttonstate == HIGH)) {
    WiFiClient client = server.available();
    if (!client) {return;}
    digitalWrite(ledPin, LOW);
    client.println("r\r");
    client.flush();
  } else {
    WiFiClient client = server.available();
    if (!client) {return;}
    digitalWrite(ledPin, LOW);
    client.println("n\r");
    client.flush();
  }
}
