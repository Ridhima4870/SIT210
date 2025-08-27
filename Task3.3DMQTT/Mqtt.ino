#include <WiFiNINA.h>       // Library to connect Arduino Nano 33 IoT to WiFi
#include <PubSubClient.h>   // Library to use MQTT protocol

// =====  WiFi credentials =====
const char* ssid = "Ridhima";       // My WiFi name (SSID)
const char* password = "ridhi1811"; // My WiFi password

// ===== Attaching MQTT broker =====
const char* mqttServer = "broker.emqx.io";   // Public EMQX MQTT broker
const int mqttPort = 1883;                   // Standard MQTT port
const char* mqttTopicWave  = "SIT210/wave";  // Topic for wave detection
const char* mqttTopicPat   = "SIT210/pat";   // Topic for pat detection

// ===== Creating Objects =====
WiFiClient wifiClient;              // WiFi client object
PubSubClient client(wifiClient);    // MQTT client object using WiFi

// ===== Defining Pins =====
const int trigPin = 2;   // Ultrasonic TRIG pin
const int echoPin = 3;   // Ultrasonic ECHO pin
const int ledPin  = 7;   // LED pin

// ===== Timing control =====
unsigned long lastWave = 0;         // Stores last wave time
unsigned long lastPat = 0;          // Stores last pat time
const unsigned long cooldown = 2000;  // 2 sec cooldown to prevent spamming

// =================================================================================
// Function: getDistance()
// This will measure distance using ultrasonic sensor and returns value 
// =================================================================================
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // pulse width (max 30 ms timeout)
  return duration * 0.034 / 2; // Convert time into distance (cm)
}

// =================================================================================
// Function: flashLED()
// This will blink the LED with a given number of times along with given delay
// =================================================================================
void flashLED(int times, int delayMs) {
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);  // LED ON
    delay(delayMs);
    digitalWrite(ledPin, LOW);   // LED OFF
    delay(delayMs);
  }
}

// =================================================================================
// Function: callback()
// It will run whenever an MQTT message is received
// =================================================================================
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message received [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  // LED reaction based on topic
  if (String(topic) == mqttTopicWave) {
    flashLED(3, 300);   // Blink LED 3 times slowly for wave
  }
  else if (String(topic) == mqttTopicPat) {
    flashLED(5, 150);   // Blink LED 5 times fast for pat
  }
}

// =================================================================================
// Function: reconnect()
// Reconnects to MQTT broker if it gets disconnected
// =================================================================================
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqttServer);
    Serial.print(":");
    Serial.println(mqttPort);

    String clientId = "Ridhima_webclient_22";   // Unique client ID
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("MQTT connected!");
      client.subscribe(mqttTopicWave);  // Subscribe to wave topic
      client.subscribe(mqttTopicPat);   // Subscribe to pat topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" (retry in 2s)");
      delay(2000);
    }
  }
}

// =================================================================================
// setup() 
// =================================================================================
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.print("Connected to WiFi! IP: ");
  Serial.println(WiFi.localIP());

  // Setup MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  // Random seed for client ID
  randomSeed(analogRead(0));
}

// =================================================================================
// loop() - runs repeatedly
// =================================================================================
void loop() {
  if (!client.connected()) {
    reconnect();   // Reconnect if needed
  }
  client.loop();   // Handle MQTT messages

  long distance = getDistance();   // Measure distance
  Serial.print("Distance: ");
  Serial.println(distance);

  // Wave detection: 50–100 cm
  if (distance >= 50 && distance <= 100 && millis() - lastWave > cooldown) {
    client.publish(mqttTopicWave, "Ridhima");
    Serial.println("➡ Published: Wave detected!");
    lastWave = millis();
  }

  // Pat detection: < 30 cm
  if (distance > 0 && distance < 30 && millis() - lastPat > cooldown) {
    client.publish(mqttTopicPat, "Ridhima");
    Serial.println("➡ Published: Pat detected!");
    lastPat = millis();
  }

  delay(200); // Small delay to reduce serial flooding
}

