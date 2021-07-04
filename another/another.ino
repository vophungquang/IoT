#include <WiFi.h>
#include <FirebaseESP32.h>
#include "DHTesp.h"
#include<stdlib.h>
 
#define DHTpin 13
DHTesp dht;
 
char buff[10];
#define FIREBASE_HOST "test-7ee35-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "ihs7g4b80CeyBJQWbpW0WKXuHYdJVi2PJv6Ia9zc"
#define WIFI_SSID "JenJus"
#define WIFI_PASSWORD "ohlahlah308"
 
 
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
 
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
 
  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */
 
  //String path = "/data";
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
