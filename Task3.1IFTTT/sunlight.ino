#include <WiFiNINA.h>
#include <Wire.h>
#include <BH1750.h>

char ssid[] = "Ridhima";       
char pass[] = "ridhi1811";   

String IFTTT_Key   = "f2GSyUyvFBIGa2kv6eeVvPdgeh15WoxT_oo94azKwlt";  //  Webhooks key
String EVENT_START = "sunlight_detected";   //defining the event start
String EVENT_STOP  = "sunlight_stopped";   //defining the event stop


BH1750 lightMeter;   //object to talk to the BH1750 sensor
WiFiSSLClient client;     //object to securely send requests to IFTTT over the internet

const int luxThreshold = 100;   // Setting threshold (100 lux) → above this = sunlight, below this = no sunlight
bool sunlightState = false;     // keeps track of current sunlight state

void setup() {
  Serial.begin(9600);  //Start serial monitor
  while (!Serial);

  // Start BH1750
  Wire.begin();
  if (lightMeter.begin()) {
    Serial.println("BH1750 ready");    //if connecting suscessful then print this message
  } else {
    Serial.println("Error starting BH1750!");  //otherwise this
  }

  // Connect to WiFi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  float lux = lightMeter.readLightLevel();  //Read light value in lux
  Serial.print("Light: ");  //Print light with the value catched on Serial Monitor
  Serial.print(lux);    //Print lux value on Serial Monitor
  Serial.println(" lx");  //Print lx on Serial Monitor

  // Check sunlight start
  if (lux > luxThreshold && !sunlightState) {
    sendToIFTTT(EVENT_START);
    sunlightState = true;
  } 
  // Check sunlight stop
  else if (lux <= luxThreshold && sunlightState) {
    sendToIFTTT(EVENT_STOP);
    sunlightState = false;
  }

  delay(5000); // check every 5 seconds
}

void sendToIFTTT(String event) {
  if (client.connect("maker.ifttt.com", 443)) {   //connect to the IFTTT Webhooks server on the internet If connection is successful, the code inside will run.If not, it will show “Connection failed”
    String url = "/trigger/" + event + "/with/key/" + IFTTT_Key;  //Builds the web address (URL) that IFTTT needs.

    client.println("GET " + url + " HTTP/1.1");   
    client.println("Host: maker.ifttt.com");
    client.println("Connection: close");  //end the request
    client.println();   //signals that I’m done sending

    Serial.print("Event sent: ");   //Prints a confirmation in Serial Monitor
    Serial.println(event);
  } else {
    Serial.println("Connection failed");   //If the Arduino cannot connect to IFTTT, it shows “Connection failed” in Serial Monitor.
  }
}
