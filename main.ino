#include <LiquidCrystal.h>

// Define button pin
#define BUTTON_PIN 2

// Initialize LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // RS, EN, D4, D5, D6, D7

unsigned long fastestReactionTime = ULONG_MAX; // Initialize to maximum possible value

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);

  // Set button pin as input
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Print initial message
  lcd.print("Quick Draw");
  lcd.setCursor(0, 1);
  lcd.print("Get ready!");
}

void loop() {
  // Wait for button press to start the game
  while (digitalRead(BUTTON_PIN) == HIGH);

  // Clear screen and prompt player to get ready
  lcd.clear();
  lcd.print("Get ready!");

  // Generate random delay before target appears
  unsigned long randomDelay = random(1000, 5000); // Random delay between 1 to 5 seconds
  delay(randomDelay);

  // Clear screen and prompt player to press the button
  lcd.clear();
  lcd.print("Press the button!");

  // Record start time
  unsigned long startTime = millis();

  // Wait for button press
  while (digitalRead(BUTTON_PIN) == HIGH);

  // Calculate reaction time
  unsigned long reactionTime = millis() - startTime;

  // Check if button was pressed too early
  if (reactionTime < randomDelay) {
    lcd.clear();
    lcd.print("Too early!");
    delay(2000);
  } else {
    // Display reaction time
    lcd.clear();
    lcd.print("Reaction Time:");
    lcd.setCursor(0, 1);
    lcd.print(reactionTime);
    lcd.print(" ms");

    // Update fastest reaction time if necessary
    if (reactionTime < fastestReactionTime) {
      fastestReactionTime = reactionTime;
      lcd.setCursor(0, 0);
      lcd.print("New Record!");
    }

    // Display fastest reaction time
    lcd.setCursor(0, 0);
    lcd.print("Fastest Time:");
    lcd.setCursor(0, 1);
    lcd.print(fastestReactionTime);
    lcd.print(" ms");

    // Delay before resetting the game
    delay(2000);
  }

  // Reset the game
  lcd.clear();
  lcd.print("Quick Draw");
  lcd.setCursor(0, 1);
  lcd.print("Get ready!");
}
