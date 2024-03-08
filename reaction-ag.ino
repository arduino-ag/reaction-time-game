#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LOOP while (true)

#define LEDgr 2
#define LEDro 3
#define SPIELER_1 4
#define SPIELER_2 5
#define START_BUTTON 6
static unsigned long timer = 0;
static int zufallwarten = 0;

void setup()
{
    randomSeed(analogRead(0));

    lcd.init();
    lcd.backlight();

    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);

    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);

    while (digitalRead(START_BUTTON) == LOW)
    {
    }

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
            lcd.println("Spieler A");
            lcd.print("hat verloren!");
            delay(5000);

            lcd.clear();
            lcd.println("RESET drücken!");

            LOOP {}
        }
        if (digitalRead(SPIELER_2) == HIGH)
        {
            lcd.clear();
            lcd.home();
            lcd.println("Spieler B");
            lcd.println("hat verloren!");
            delay(5000);

            lcd.clear();
            lcd.println("RESET drücken!");

            LOOP {}
        }
    }

    digitalWrite(LEDgr, HIGH);

    LOOP
    {
        if (digitalRead(SPIELER_1) == HIGH)
        {
            lcd.clear();
            lcd.home();
            lcd.println("Spieler A");
            lcd.println("gewinnt!");

            LOOP {}
        }
        if (digitalRead(SPIELER_2) == HIGH)
        {
            lcd.clear();
            lcd.home();
            lcd.println("Spieler B");
            lcd.println("gewinnt!");

            LOOP {}
        }
    }
}
