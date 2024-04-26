#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LEDgr 2
#define LEDro 3
#define SPIELER_1 4
#define SPIELER_2 5
#define START_BUTTON 6
#define RESET_PIN 7

static unsigned long timer = 0;
static int zufallwarten = 0;

#define LOOP while (true)
#define RESET digitalWrite(RESET_PIN, LOW)

void setup()
{
    digitalWrite(RESET_PIN, HIGH);

    randomSeed(analogRead(0));

    lcd.init();
    lcd.backlight();

    pinMode(LEDgr, OUTPUT);
    pinMode(LEDro, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);

    pinMode(SPIELER_1, INPUT);
    pinMode(SPIELER_2, INPUT);
    pinMode(START_BUTTON, INPUT);

    while (digitalRead(START_BUTTON) == LOW)
    {
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Spiel beginnt!");

    delay(500);

    timer = millis();
    lcd.clear();

    zufallwarten = random(0, 20000);
}

void loop()
{
    while ((millis() - timer) < zufallwarten)
    {
        if (digitalRead(SPIELER_1) == HIGH)
        {
            lcd.clear();
            lcd.home();
            lcd.print("Spieler A");
            lcd.setCursor(0, 1);
            lcd.print("hat verloren!");
            delay(5000);

            lcd.clear();
            lcd.home();
            lcd.print("RESET drücken!");

            delay(5000);

            RESET;
        }

        if (digitalRead(SPIELER_2) == HIGH)
        {
            lcd.clear();
            lcd.home();
            lcd.print("Spieler B");
            lcd.setCursor(0, 1);
            lcd.print("hat verloren!");
            delay(5000);

            lcd.home();
            lcd.clear();
            lcd.print("RESET drücken!");

            delay(5000);

            RESET;
        }
    }

    digitalWrite(LEDgr, HIGH);

    LOOP
    {
        if (digitalRead(SPIELER_1) == HIGH)
        {
            lcd.clear();
            lcd.home();
            lcd.print("Spieler A");
            lcd.setCursor(0, 1);
            lcd.print("gewinnt!");

            delay(5000);

            RESET;
        }

        if (digitalRead(SPIELER_2) == HIGH)
        {
            lcd.clear();
            lcd.home();
            lcd.print("Spieler B");
            lcd.setCursor(0, 1);
            lcd.print("gewinnt!");

            delay(5000);

            RESET;
        }
    }
}
