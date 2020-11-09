// just a bit of code that gives realtime readouts for all inputs to the LCD
// thought itd be a neat tool for debug later on
#include <Wire.h>
#include "DFRobot_RGBLCD.h"

const int colorR = 255;
const int colorG = 255;
const int colorB = 255;
int potpin = A3;
int ypin = A2;
int xpin = A1;

DFRobot_RGBLCD lcd(16,2);  //16 characters and 2 lines of show

void setup() {
    // initialize
    lcd.init();
    lcd.setRGB(colorR, colorG, colorB);
    pinMode(7, INPUT);
}

void loop() {
    lcd.setCursor(5, 0);
    lcd.print(" ");
    lcd.setCursor(0, 0);
    lcd.print("Y:");
    lcd.print(analogRead(ypin));
    lcd.setCursor(7, 0);
    lcd.print("B:");
    if (digitalRead(7)==HIGH)
    {lcd.print("HI");}
    else
    {lcd.print("LO");}
    lcd.print(" J:");
    if (digitalRead(6)==HIGH)
    {lcd.print("HI");}
    else
    {lcd.print("LO");}
    lcd.setCursor(5, 1);
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print("X:");
    lcd.print(analogRead(xpin));
    lcd.setCursor(13, 1);
    lcd.print(" ");
    lcd.setCursor(7, 1);
    lcd.print(" S:");
    lcd.print(analogRead(potpin));

    delay(100);
}
