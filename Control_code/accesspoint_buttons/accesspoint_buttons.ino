#include <ESP8266WiFi.h>

// accesspoint will have two buttons that when pressed, will activate either a left or right LED on the station board.

// constants
WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);
byte ledPin = 2;
const int leftbutton = 5;
const int rightbutton = 4;

// variables
int leftbuttonstate = 0;
int rightbuttonstate = 1;
//String/ state = "";
String st = "";

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

  st = checkbuttons();

  if (st == "") {
    while (st == "") {
      delay(100);
      Serial.println("in pergatory");
      String ans = checkbuttons();
      if (ans != "") {
        st == ans;
      }
    }
  }
  if (st == "lr") {
    while (st == "lr") {
      Serial.println(st);
      WiFiClient client = server.available();
      client.println("lr\r");
      String ans = checkbuttons();
      if (ans == "lr") {
        client.println("off\r");
        st == "";
      } else if (ans != "") {
        st == ans;
      }
      client.flush();
      delay(250);
    }
  } else if (st == "l") {
    while (st == "l") {
      Serial.println(st);
      WiFiClient client = server.available();
      client.println("l\r");
      String ans = checkbuttons();
      if (ans == "l") {
        client.println("off\r");
        st == "";
      } else if (ans != "") {
        st == ans;
      }
      client.flush();
      delay(250);
    }
  } else if (st == "r") {
    while (st == "r") {
      Serial.println(st);
      WiFiClient client = server.available();
      client.println("r\r");
      String ans = checkbuttons();
      if (ans == "r") {
        client.println("off\r");
        st == "";
      } else if (ans != "") {
        st == ans;
      }
      client.flush();
      delay(250);
    }
  }
}

String checkbuttons() {
  String state = "";
  // get current button states
  leftbuttonstate = digitalRead(leftbutton);
  rightbuttonstate = digitalRead(rightbutton);
  // set button states to operational state
  if ((leftbuttonstate == HIGH) && (rightbuttonstate == HIGH)) {
    state = "lr";
  } else if((leftbuttonstate == HIGH) && (rightbuttonstate == LOW)) {
    state = "l";
  } else if((leftbuttonstate == LOW) && (rightbuttonstate == HIGH)) {
    state = "r";
  } else {
    state = "";
  }
  //Serial.println(state);
  return state;
}
