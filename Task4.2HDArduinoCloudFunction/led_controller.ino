#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>

const char* ssid = "Ridhima";
const char* password = "ridhi1811";

#define FIREBASE_HOST "arduino-led-control-ec260-default-rtdb.firebaseio.com"  
#define FIREBASE_AUTH "YaNMCUK6dfK96afVkqc1xnfWIYF6A66kKXJoQspa"     

const int redPin = 2;   //defiening the pins
const int greenPin = 3;
const int bluePin = 4;

FirebaseData fbdo;


void setup() {
  Serial.begin(9600);     //setting up trhe serial baurd rate
  pinMode(redPin, OUTPUT);      //setting each pin as output
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

 
  Firebase.reconnectWiFi(true);  // make firebase recconent if the wifi drops

  
  Serial.print("Connecting to WiFi");       //connecting gto the wifi and prinitin messages
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  // Now start Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, password);
  Serial.println("Firebase initialized!");
}

void toggleLED(String color) {
  if (color == "red") digitalWrite(redPin, !digitalRead(redPin));
  else if (color == "green") digitalWrite(greenPin, !digitalRead(greenPin));
  else if (color == "blue") digitalWrite(bluePin, !digitalRead(bluePin));
}

void loop() {
  if (Firebase.getString(fbdo, "ledCommand")) {  //reading the led command from firbase
    String command = fbdo.stringData();    //get string from fbdo
    if (command != "") {
      Serial.println("Command received: " + command);
      toggleLED(command);                                //is suscessful  then toogle led
      Firebase.setString(fbdo, "ledCommand", "");  // reseting variable in firebase
    }
  }
  delay(500);
}
