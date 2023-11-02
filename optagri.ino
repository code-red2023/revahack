  
#include "DHT.h"

#define DHTPIN 4  
#define DHTTYPE DHT11  
int _moisture,sensor_analog;
const int sensor_pin = A0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  // put your setup code here, to run once:

}

void loop() {
   sensor_analog = analogRead(sensor_pin);
 //  moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
  Serial.print("Moisture = ");
  Serial.print(sensor_analog);  /* Print Temperature on the serial window */
  Serial.println("");
  float hum = dht.readHumidity();
  float tem = dht.readTemperature();

  if (isnan(hum) || isnan(tem)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print("%, Temperature: ");
    Serial.print(tem);
    Serial.println("°C");
  }
  delay(1000);  

}
