#include <Arduino.h>    // Core Arduino functions
#include <Ticker.h>     // Timer library (Stefan Staub version)
#include <DHT.h>        // DHT sensor library

// ================== Pin Definitions ==================
const uint8_t BUTTON_PIN = 2;       // Button on D2 (external interrupt)
const uint8_t TRIG_PIN   = 3;       // Ultrasonic trigger pin
const uint8_t ECHO_PIN   = 4;       // Ultrasonic echo pin
const uint8_t DHT_PIN    = 5;       // DHT22 data pin

const uint8_t LED1_PIN   = 10;      // LED1 toggled by button ISR
const uint8_t LED2_PIN   = 11;      // LED2 toggled by ultrasonic condition
const uint8_t LED3_PIN   = LED_BUILTIN; // Built-in LED toggled by timer ISR

volatile bool buttonFlag = false;   // Flag set by button ISR
volatile uint32_t lastBtnMicros = 0; // For button debounce (just for microseconds)

// ================== DHT22 Sensor Setup ==================
#define DHTTYPE DHT22
DHT dht(DHT_PIN, DHTTYPE);          // Creating DHT object

// ================== Ultrasonic Function ==================
long readUltrasonicCM() {
  digitalWrite(TRIG_PIN, LOW);      // Ensure trigger low
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);     // Send 10us pulse
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // Measure echo duration
  long distance = duration / 58;   // Convert to cm
  return distance;
}

// ================== Timer Task (runs every 1s) ==================
void timerTask() {
  digitalWrite(LED3_PIN, !digitalRead(LED3_PIN));  // Toggle built-in LED

  long distance = readUltrasonicCM();              // Read distance
  if (distance > 0 && distance < 20) {             // If object <20cm
    digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));// Toggle LED2
    Serial.print("[TIMER] Object detected at ");
    Serial.print(distance);
    Serial.println(" cm -> LED2 toggled");
  } else {                                         // Otherwise just log
    Serial.print("[TIMER] Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Read DHT22 values
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {                      // This Checks if it is valid
    Serial.println("[TIMER] Failed to read from DHT22!");
  } else {
    Serial.print("[TIMER] Humidity: ");
    Serial.print(h);
    Serial.print(" % | Temperature: ");
    Serial.print(t);
    Serial.println(" °C");
  }
}

// ================== Button Interrupt Service Routine ==================
void ISR_button() {
  uint32_t now = micros();                         
  if (now - lastBtnMicros > 200000UL) {            // Debounce (200ms)
    buttonFlag = true;                             // Set flag
    lastBtnMicros = now;                           // Update last press time
  }
}

// ================== Timer Setup ==================
Ticker timer1(timerTask, 1000);   // Call timerTask every 1000ms (1s)

// ================== Setup ==================
void setup() {
  Serial.begin(115200);
  while (!Serial) {}                                // Wait for serial
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);                // Button uses pull-up
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), ISR_button, FALLING);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  dht.begin();                                      // Start DHT22
  timer1.start();                                   // Start timer
  Serial.println("System has detected the sensor interrupt. Loading data:");
}

// ================== Main Loop ==================
void loop() {
  timer1.update();                                  // Update timer
  if (buttonFlag) {                                 // If button was pressed
    buttonFlag = false;                             // Reset flag
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN)); // Toggle LED1
    Serial.println("[INT] Button pressed -> LED1 toggled");
  }
}
