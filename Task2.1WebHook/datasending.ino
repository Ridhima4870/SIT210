#include "DHT.h"
#include <WiFiNINA.h>
#include "ThingSpeak.h"

// DHT22 configuration
#define DHTPIN 2         
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials of my  network
char ssid[] = "Verma Home 4G";     
char pass[] = "vermahouse"; 

// ThingSpeak credentials
unsigned long myChannelNumber = 3024682;               
const char * myWriteAPIKey = "N81I8SFQTJI86F4A";      

WiFiClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Wait for serial monitor to open

  dht.begin();
  delay(2000);      // stabilizing the sensor

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {  // This loop keeps checking until the board is connected to WiFi
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi!");
  ThingSpeak.begin(client);    // Now I'm starting the ThingSpeak connection using WiFi client
}

void loop() {
  float temperature = dht.readTemperature();    //reading temperature from the DHT sensor
  float humidity = dht.readHumidity();         //reading humidity from the DHT sensor

  if (isnan(temperature) || isnan(humidity)) {        // If the sensor didn’t give any valid data
    Serial.println("Failed to read from DHT sensor!");    // Show error message in Serial Monitor
    delay(30000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  ThingSpeak.setField(1, temperature);     // Here I am putting temperature in Field 1 of ThingSpeak
  ThingSpeak.setField(2, humidity);        // Here I am putting humidity in Field 2 of ThingSpeak

  int status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);   // Sending both values to ThingSpeak

  if (status == 200) {           // 200 means data was sent successfully
    Serial.println("Data sent to ThingSpeak!");
  } else {
    Serial.print("Failed to send data. Error code: ");
    Serial.println(status);
  }

  delay(30000);  // Wait 30 seconds before sending next update
}
