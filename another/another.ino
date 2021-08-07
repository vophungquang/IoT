#include <WiFi.h>
#include <FirebaseESP32.h>
#include "DHTesp.h"
#include<stdlib.h>
 
#define DHTpin 13
DHTesp dht;
 
char buff[10];
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
 
 
//Define FirebaseESP32 data object
FirebaseData firebaseData;
FirebaseJson json;
 
 
String mytemp; 
String myhum;
void setup()
{
 
   Serial.begin(115200);
   dht.setup(DHTpin, DHTesp::DHT11);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
 
  Serial.println("------------------------------------");
  Serial.println("Connected...");
  
}
 
void loop()
{
   delay(dht.getMinimumSamplingPeriod());
 
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  myhum = dtostrf(humidity,3,2,buff);
  mytemp = dtostrf(temperature,3,2,buff);
  Serial.println(myhum);
  Serial.println(mytemp);
   
delay(100); 
 json.set("/hum", myhum);
 json.set("/temp", mytemp);
 Firebase.updateNode(firebaseData,"/Sensor",json);
 
}
