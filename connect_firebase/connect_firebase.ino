#include <ESP8266WiFi.h>
#include <DHT.h>

#include <FirebaseArduino.h>

#include<SoftwareSerial.h>

SoftwareSerial  mySerial(D5, D6);

#define DHTPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define WIFI_SSID "Thanh_T2"
#define WIFI_PASSWORD "@9999999"
#define FIREBASE_HOST "st-project-49044-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "jVpXSuWn2taIHr4oqMBIa03tOduRW8tw6NoRdgrs"

int LED1 = D2;

String text;


void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(DHTPIN, INPUT);
  delay(2000);
  Serial.println('\n');
  wifiConnect();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(10);
  dht.begin();

  mySerial.begin(9600);
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  Firebase.setString("Temp", String(t));
  Serial.println(t);
  Serial.println(h);
  Firebase.setString("Hum", String(h));

  text = Firebase.getString("LCD");

  // Serial.print(Firebase.getString("LED1") + "\n");
  digitalWrite(LED1, Firebase.getString("LED1").toInt());
  delay(10);
  mySerial.println(text);
  if (WiFi.status() != WL_CONNECTED) {
    wifiConnect();
  }
  delay(10);
}

void wifiConnect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  Serial.println(" ...");

  int teller = 0;
  while (WiFi.status() != WL_CONNECTED) {  // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++teller);
    Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());  // Send the IP address of the ESP8266 to the computer
}