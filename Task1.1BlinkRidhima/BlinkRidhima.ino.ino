#define LED_PIN 13  

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  blinkMorse(".-.");  // R
  letterPause();
  blinkMorse("..");   // I
  letterPause();
  blinkMorse("-..");  // D
  letterPause();
  blinkMorse("...."); // H
  letterPause();
  blinkMorse("..");   // I
  letterPause();
  blinkMorse("--");   // M
  letterPause();
  blinkMorse(".-");   // A
  wordPause();
}

// Blink the LED for each dot or dash
void blinkMorse(String code) {
  for (int i = 0; i < code.length(); i++) {
    if (code[i] == '.') {
      dot();
    } else if (code[i] == '-') {
      dash();
    }
    delay(250);  
  }
}

// Dot = short blink
void dot() {
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
}

// Dash = long blink
void dash() {
  digitalWrite(LED_PIN, HIGH);
  delay(750);
  digitalWrite(LED_PIN, LOW);
}

// For pause between letters
void letterPause() {
  delay(1000);
}

void wordPause() {
  delay(2000);
}

