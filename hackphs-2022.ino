/*
 * lcd_bar_graph.ino
 * Displays a simple bar graph
 * 
 * Sahibjot Singh
 * December 20, 2020
 */


#include <LiquidCrystal.h>

// LCD Screens
LiquidCrystal lcd1{ 12, 11, 10, 9, 8, 7 };
LiquidCrystal lcd2{ 6, 5, 4, 3, 2, 13 };

// Buttons
const byte addButton = A3;
const byte subButton = A4;
const byte entButton = A5;
bool buttonValues[3] = { false, false, false };

// Variables
int num = 0;
int num2 = 0;
int numCount = 0;
int playerCount = 0;

//
int displayRandom(LiquidCrystal& lcd) {
  int count = 0;
  for (size_t i = 0; i < 16; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      if (random(1, 5) == 1) {
        lcd.setCursor(i, j);
        lcd.print(".");
        count++;
      }
    }
  }
  return count;
}

// Executes once, at the start
void setup() {
  randomSeed(analogRead(0));
  
  // Initializes the LCDs
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  lcd1.clear();
  lcd2.clear();

  Serial.begin(9600);
  numCount = displayRandom(lcd1);
}

// Loops infinitely
void loop() {
  bool currentButtonValues[3] = {
    digitalRead(addButton),
    digitalRead(subButton),
    digitalRead(entButton)
  };
  
  // Button inputs
  for (size_t i = 0; i < 3; ++i) {
    if (currentButtonValues[i] && currentButtonValues[i] != buttonValues[i]) {
      Serial.println(currentButtonValues[0]);
      Serial.println(currentButtonValues[1]);
      Serial.println(currentButtonValues[2]);

      Serial.println(buttonValues[0]);
      Serial.println(buttonValues[1]);
      Serial.println(buttonValues[2]);
      switch (i) {
      case 0:
        if (playerCount == 16) lcd2.setCursor(0, 1);
        lcd2.print(".");
        playerCount++;
        break;
      case 1:
        playerCount--;
        lcd2.setCursor(playerCount % 16, playerCount / 16);
        lcd2.print(" ");
        lcd2.setCursor(playerCount % 16, playerCount / 16);
        break;
      case 2:
        if (playerCount == numCount) {
          lcd1.clear();
          lcd2.clear();
          lcd1.print("You won");
          lcd2.print("Press reset");
          lcd2.setCursor(0, 1);
          lcd2.print(" to replay");
        } else {
          lcd1.clear();
          lcd2.clear();
          lcd1.print("You lost");
          lcd2.print("Press reset");
          lcd2.setCursor(0, 1);
          lcd2.print(" to replay");
        }
      }
    }
    buttonValues[i] == currentButtonValues[i];
  }

  delay(100);
}
