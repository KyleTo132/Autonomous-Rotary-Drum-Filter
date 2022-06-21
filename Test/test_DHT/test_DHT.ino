#include <FirebaseESP8266.h>
#include  <ESP8266WiFi.h>
#include "DHT.h"

#define FIREBASE_HOST "https://fir-iot-db-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define WIFI_SSID "TOOF" // Change the name of your WIFI
#define WIFI_PASSWORD "tuananhto132" // Change the password of your WIFI
#define FIREBASE_Authorization_key "FcllB6N6dC0a7nklFMROJw39RdLoQkFrhjMcj5N6"

#define DHTPIN 12    

#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

FirebaseData firebaseData;
FirebaseJson json;

void setup() {

 Serial.begin(9600);
  dht.begin();
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
  
}

void loop() {
 
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();  
  
   if (isnan(hum) || isnan(temp)  ){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("°C");
  Serial.print(" Humidity: ");
  Serial.print(hum);
  Serial.print("%");
  Serial.println();

  Firebase.setFloat(firebaseData, "/ESP8266_APP/TEMPERATURE", temp);
  Firebase.setFloat(firebaseData, "/ESP8266_APP/HUMIDITY", hum);
   delay(200);
}
