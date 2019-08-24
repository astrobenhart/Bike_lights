#include <ESP8266WiFi.h>

// station will have two sets of leds that will activate when a button for each set is pressed on the accesspoint board.

// constants
byte ledPin = 2;
const int leftled = 0;
const int rightled = 1;
char ssid[] = "ESP_access";           // SSID of your AP
char pass[] = "andr0m3da";         // password of your AP
IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

// variables
String state = "";

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
}

void loop() {
  while (state == "") {
    digitalWrite(leftled, LOW);
    digitalWrite(rightled, LOW);
    delay(100);
    client.connect(server, 80);
    digitalWrite(ledPin, LOW);
    String answer = client.readStringUntil('\r');
    if (answer != "") {
        state = answer;
    }
  }
  if (state == "lr") {
    while (state == "lr") {
      Serial.print("turning on both left and right leds");
      digitalWrite(leftled, HIGH);
      digitalWrite(rightled, HIGH);
      delay(600);
      digitalWrite(leftled, LOW);
      digitalWrite(rightled, LOW);
      delay(600);
      String answer = client.readStringUntil('\r');
      if (answer != "") {
        state = answer;
      } else if (answer == state) {
        state = "";
      }
    } 
  } else if (state == "l") {
    while (state == "l") {
      Serial.print("turning on left leds");
      digitalWrite(leftled, HIGH);
      digitalWrite(rightled, LOW);
      delay(600);
      digitalWrite(leftled, LOW);
      digitalWrite(rightled, LOW);
      delay(600);
      String answer = client.readStringUntil('\r');
      if (answer != "") {
        state = answer;
      } else if (answer == state) {
        state = "";
      }
    }
  } else if (state == "r") {
    while (state == "r") {
      Serial.print("turning on right leds");
      digitalWrite(leftled, LOW);
      digitalWrite(rightled, HIGH);
      delay(600);
      digitalWrite(leftled, LOW);
      digitalWrite(rightled, LOW);
      delay(600);
      String answer = client.readStringUntil('\r');
      if (answer != "") {
        state = answer;
      } else if (answer == state) {
        state = "";
      }
    }
  }
  client.flush();
  digitalWrite(ledPin, HIGH);
  client.stop();
  delay(100);
}

  
//  client.connect(server, 80);
//  digitalWrite(ledPin, LOW);
//  String answer = client.readStringUntil('\r');
//  if (answer != "");
//  if (answer != "n") {
//    state = answer;
//  }
//  if (state == "lr") {
//    Serial.print("turning on both left and right leds");
//    digitalWrite(leftled, HIGH);
//    digitalWrite(rightled, HIGH);
//    delay(1000);
//    digitalWrite(leftled, LOW);
//    digitalWrite(rightled, LOW);
//    delay(900);
//  }
//  else if (state == "l") {
//    Serial.print("turning on left leds");
//    digitalWrite(leftled, HIGH);
//    digitalWrite(rightled, LOW);
//    delay(1000);
//    digitalWrite(leftled, LOW);
//    digitalWrite(rightled, LOW);
//    delay(900);
//  }
//  else if (state == "r") {
//    Serial.print("turning on right leds");
//    digitalWrite(leftled, LOW);
//    digitalWrite(rightled, HIGH);
//    delay(1000);
//    digitalWrite(leftled, LOW);
//    digitalWrite(rightled, LOW);
//    delay(900);
//  }
//  client.flush();
//  digitalWrite(ledPin, HIGH);
//  client.stop();
//  delay(100);
//}
