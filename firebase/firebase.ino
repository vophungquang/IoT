#include "WiFi.h"
#include <FirebaseESP32.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DHT.h>

const char* ssid = "JenJus";
const char* pass = "ohlahlah308";

#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float tem;
float hum;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
const long gmtOffset_sec = 7 * 60 * 60;

// Variables Firebase
//#define FIREBASE_HOST "test-7ee35-default-rtdb.firebaseio.com"
//#define FIREBASE_AUTH "ihs7g4b80CeyBJQWbpW0WKXuHYdJVi2PJv6Ia9zc"
#define FIREBASE_HOST "projectiot-d1c40-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "7eab3pUVBT99Nm2dynveYmXZBv3T4UzqRggW78nf"     
FirebaseData firebaseData;
FirebaseJson json;
String epochTime;
String path;

void setup() {
  Serial.begin(115200);
  // WiFi Start
  Serial.println("Connect network:");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());;

  timeClient.begin();
  timeClient.setTimeOffset(gmtOffset_sec);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  dht.begin();
}

void loop() {
  
  while(WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(". - . ");
  }
  
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  tem = dht.readTemperature();
  hum = dht.readHumidity();
  epochTime = timeClient.getEpochTime();
//  path = "/data/T-" + epochTime;
  path="/data/ESP32";

  if( isnan(tem) || isnan(hum) ){
    Serial.println("----------------  ERROR ----------------");
    Serial.println("Error: sensor DHT11");
    Serial.println("--------------------------------");
    
    sendError(epochTime, 111);
  } else {
    
    json.clear();
    json.add("tem", tem);
    json.add("hum", hum);
    json.add("time", timeClient.getFormattedDate());

    if (Firebase.setJSON(firebaseData, path, json)) {
      Serial.println("SEND SUCCESS");
      delay(1000*20);
        
    } else {
        Serial.println("FAILED");
        Serial.println("REASON: " + firebaseData.errorReason());
        Serial.println("------------------------------------");
        Serial.println();
    }
  }
  delay(30000);
}

void sendError(String epochTime, int codeError) {
  String pathError = "error/T-" + epochTime;
  FirebaseJson jsonError;
  jsonError.clear();
  jsonError.add("code", codeError);
  jsonError.add("epochTime", epochTime);

  switch (codeError) {
    case 111:
      jsonError.add("msj", "DHT11 - NaN value temperature or humidity");
      break;
    default:
      Serial.println("Error not found");
      break;
  }

  if (Firebase.setJSON(firebaseData, pathError, jsonError)) {
      Serial.println("SEND ERROR SUCCESS");
      delay(1000*20);
        
    } else {
        Serial.println("SEND ERROR FAILED");
        Serial.println("REASON: " + firebaseData.errorReason());
        Serial.println("------------------------------------");
        Serial.println();
        delay(1000);
    }
}
