#include <ESP8266WiFi.h>

// accesspoint will have two buttons that when pressed, will activate either a left or right LED on the station board.

// constants
WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);
byte ledPin = 2;
const int leftbutton = 0;
const int rightbutton = 1;

// variables
int leftbuttonstate = 0;
int rightbuttonstate = 0;

void setup() {
 Serial.begin(9600);
 WiFi.mode(WIFI_AP);
 WiFi.softAP("ESP_access", "andr0m3da");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
 pinMode(ledPin, OUTPUT);
 pinMode(leftbutton, INPUT);
 pinMode(rightbutton, INPUT);
 Serial.println();
 Serial.println("Server started.");
 Serial.print("IP: "); Serial.println(WiFi.softAPIP());
 Serial.print("MAC:"); Serial.println(WiFi.softAPmacAddress());
}
void loop() {
   leftbuttonstate = digitalRead(leftbutton);
   rightbuttonstate = digitalRead(rightbutton);
   WiFiClient client = server.available();
   digitalWrite(ledPin, LOW);
   if (!client) {return;}
   if ((leftbuttonstate == HIGH) && (rightbuttonstate == HIGH)) {
      Serial.print("left and right buttons pressed");
      client.println("lr\r");
   }
   else if((leftbuttonstate == HIGH) && (rightbuttonstate == LOW)) {
      Serial.print("only left button pressed");
      client.println("l\r");
   }
   else if((leftbuttonstate == LOW) && (rightbuttonstate == HIGH)) {
      Serial.print("only right button pressed");
      client.println("r\r");
   }
   else {
    client.println("n\r");
   }
   delay(500);
  }
