  
#include "DHT.h"

#define DHTPIN 4  
#define DHTTYPE DHT11 
 #include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino_JSON.h> 
int _moisture,sensor_analog;
int relayPin = 4;

const int sensor_pin = A0;
const char* ssid = "linkesh";
const char* password = "20042004";
String outputdata ;
int wait;

DHT dht(DHTPIN, DHTTYPE);
String URL = "https://pro.openweathermap.org/data/2.5/forecast/hourly?";
String ApiKey = "e4d7c8e138b5339578a5241efff65332";
String lat = "10.75547984242798";
String lon = "78.65237086014207";
float water_threshold = 4  ;
float soil_moisture_threshold = 80; 
float temperature_threshold = 24  ;
float humidity_threshold = 60  ;
void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(relayPin,OUTPUT);
    WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

 // Serial.println("");
  //Serial.println("WiFi connected.");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());
}
  // put your setup code here, to run once:


void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    //Set HTTP Request Final URL with Location and API key information
    http.begin(URL + "lat=" + lat + "&lon=" + lon + "&appid=" + ApiKey + "&units=metric");

    // start connection and send HTTP Request
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {

      //Read Data as a JSON string
      String JSON_Data = http.getString();
    //  Serial.println(JSON_Data);

      //Retrieve some information about the weather from the JSON format
      DynamicJsonDocument doc(ESP.getMaxAllocHeap());
      deserializeJson(doc, JSON_Data);
      sensor_analog = analogRead(sensor_pin);
      int moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
     // Serial.print("Moisture = ");
      //Serial.println(sensor_analog);  /* Print Temperature on the serial window */
     //Serial.println("");
     float hum = dht.readHumidity();
     float tem = dht.readTemperature();
      JsonArray weather_list = doc["list"].as<JsonArray>();

    //Serial.println(weather_list);

  // Iterate through the weather data
  for (JsonObject item : weather_list) {
    // Access specific data within each item
    long timestamp = item["dt"];
    float temperature = item["main"]["temp"];
    float feels_like = item["main"]["feels_like"];
    const char* weather_description = item["weather"][0]["description"];
    float wind_speed = item["wind"]["speed"];
    float rain = item["rain"]["1h"]; 
    float rain_predict = item["pop"];
 //   Serial.println(rain_predict);
//    Serial.println(timestamp);
//    Serial.println(temperature);
//    Serial.println(feels_like);
//    Serial.println(weather_description);
//    Serial.println(wind_speed);
//    Serial.println(rain);
    
  delay(1000);  

  if (isnan(hum) || isnan(tem)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    outputdata = String(timestamp)+","+String(tem)+","+String(hum)+","+String(weather_description)+","+String(rain)+","+String(rain_predict)+","+String(moisture);
//    Serial.print("Humidity: ");
    Serial.println(outputdata);
     // Implement your decision-making logic
  if (rainpredict > 0.5) {
    if (rainfall < water_threshold) {
      wait =(( water_threshold - rainfall)*10/1000)/8*3600000
      if (moisture < soilmoisture_threshold) {
        // You can add the BME280 sensor reading here if you're using it
        // float temperature = bme.readTemperature();
        // float humidity = bme.readHumidity();

        if ( temperature > temperature_Threshold && humidity < humidity_Threshold ) {
          // Implement irrigation control logic here
            digitalWrite(relayPin,HIGH);
            delay(wait);
  // put your main code here, to run repeatedly:
            digitalWrite(relayPin,LOW);
             delay(10000);
  
          Serial.println("Initiating irrigation...");
        } else {
          Serial.println("No irrigation needed.");
        }
      } else {
        Serial.println("No irrigation needed.");
      }
    } else {
      Serial.println("Rainfall detected. No irrigation needed.");
    }
  }

  // Add a delay if needed to prevent rapid decision-making and printing
  delay(1000);  // Wait for 1 second before making another decision
}}
// 
//    Serial.print(tem);
//    Serial.println("°C");






 }
   

     


  }    } else {
      Serial.println("Error!");
      // Serial.println.clear();
      Serial.println("Can't Get DATA!");
    }

    http.end();

  
  
  //Wait for 30 seconds
  delay(30000);
}
