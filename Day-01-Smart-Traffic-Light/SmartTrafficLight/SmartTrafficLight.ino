// ESP32 Pin Definitions
const int LED_RED    = 23; 
const int LED_YELLOW = 22; 
const int LED_GREEN  = 21; 
const int BTN_PEDS   = 4;  

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BTN_PEDS, INPUT);
}

void loop() {
  // Default State: Green light for vehicles
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);

  // Check if pedestrian button is pressed
  if (digitalRead(BTN_PEDS) == HIGH) {
    delay(500); // Debounce delay
    
    // Switch to Yellow
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    delay(2000); 

    // Switch to Red (Pedestrians can cross)
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
    delay(5000);

    // Transition back to Green
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
    delay(1000);
  }
}