#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

// Keypad
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys),
                       rowPins, colPins,
                       ROWS, COLS);

String number = "";

void setup()
{
  servo.attach(10);

  lcd.init();
  lcd.backlight();

  servo.write(0);

  lcd.setCursor(0, 0);
  lcd.print("Enter Degree:");
  lcd.setCursor(0, 1);
}

void loop()
{
  char key = keypad.getKey();

  if (key)
  {
    // Number keys
    if (key >= '0' && key <= '9')
    {
      number += key;
      lcd.print(key);
    }

    // # = Move servo
    if (key == '#')
    {
      int degree = number.toInt();

      if (degree >= 0 && degree <= 180)
      {
        servo.write(degree);

        lcd.clear();
        lcd.print("Servo Angle:");
        lcd.setCursor(0, 1);
        lcd.print(degree);
        lcd.print(" Degree");
      }
      else
      {
        lcd.clear();
        lcd.print("Enter 0-180");
      }

      number = "";
      delay(1000);

      lcd.clear();
      lcd.print("Enter Degree:");
      lcd.setCursor(0, 1);
    }

    // * = Clear
    if (key == '*')
    {
      number = "";
      lcd.clear();
      lcd.print("Enter Degree:");
      lcd.setCursor(0, 1);
    }
  }
}
