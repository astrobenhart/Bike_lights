#include <ESP8266WiFi.h>

// constants
byte ledPin = 2;
int leftled = 13;
int rightled = 4;
char ssid[] = "ESP_access";           // SSID of your AP
char pass[] = "andr0m3da";         // password of your AP
IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

// variables

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  pinMode(ledPin, OUTPUT);
  pinMode(leftled, OUTPUT);
  pinMode(rightled, OUTPUT);
}
void loop() {
  client.connect(server, 80);
  digitalWrite(ledPin, LOW);
  String answer = client.readStringUntil('\r');
  if (answer == "l") {
    digitalWrite(leftled, HIGH);
    digitalWrite(rightled, LOW);
    delay(200);
    digitalWrite(leftled, LOW);
    digitalWrite(rightled, LOW);
    delay(200);
  } else if (answer == "r") {
    digitalWrite(leftled, LOW);
    digitalWrite(rightled, HIGH);
    delay(200);
    digitalWrite(leftled, LOW);
    digitalWrite(rightled, LOW);
    delay(200);
  } else {
    digitalWrite(leftled, LOW);
    digitalWrite(rightled, LOW);
    delay(100);
  }
}
