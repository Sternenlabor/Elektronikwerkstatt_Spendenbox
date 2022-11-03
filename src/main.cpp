#include <Arduino.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// output control pins
#define LCD_CONTRAST_PIN 6
#define LCD_BACKLIGHT_PIN 10

void setup() {
  analogWrite(LCD_BACKLIGHT_PIN, 255); //set backlight on
  analogWrite(LCD_CONTRAST_PIN, 90); //set some contrast

  lcd.begin(16, 2);

  lcd.setCursor(3, 0);
  lcd.print("SPENDENBOX");
}

int i = 0;
int dir = 1;
int scrollDur = 30;
int scroll = 0;
int scrollDir = 1;
int pad = 0;

void loop() {

  // loop through values for backlight
  if (i <= 20) {
    dir = 1;
  }
  else if (i >= 255) {
    dir = -1;
  }
  i += dir;
  analogWrite(LCD_BACKLIGHT_PIN, i);

  //scroll display
  if (scroll++ > scrollDur) {
    scroll = 0;

    // clear
    lcd.setCursor(0, 1);
    lcd.print("                ");

    lcd.setCursor(pad, 1);
    lcd.print("=");
    
    pad += scrollDir;
    if (pad >= 15) {
      scrollDir = -1;
    }
    else if (pad <= 0) {
      scrollDir = 1;
    }
  }

  delay(10);
}