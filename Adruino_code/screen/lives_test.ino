// this is not an exact function, just messing around with 
// drawing hearts, removing them, changing the message
// things like that
#include <Wire.h>
#include "DFRobot_RGBLCD.h"

DFRobot_RGBLCD lcd(16,2);  //16 characters and 2 lines of show

unsigned long start;
int lives =3;
// custom symbol heart
byte heart[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

void setup() 
{
  lcd.init();
  lcd.customSymbol(0, heart);
  pinMode(7, INPUT);
  lcd.setCursor(13, 0);
  lcd.write((unsigned char)0);
  lcd.write((unsigned char)0);
  lcd.write((unsigned char)0);
}

void loop() {
  lcd.setRGB(255, 255, 255);
  lcd.setCursor(0, 0);
  lcd.print("play  ");
  if (digitalRead(7)==HIGH)
    {
       lives= lives-1;
       if (lives==0)
       {
       lcd.setRGB(255, 0, 0);
       lcd.setCursor(13, 0);
       lcd.write("   ");
       lcd.setCursor(0, 0);
       lcd.print("YOU LOSE! ");
       lcd.print("RESET");
       while(1==1){}
       }
       lcd.setCursor(0, 0);
       lcd.print("WRONG!");
       lcd.setCursor(13, 0);
       if (lives == 2)
       {
        lcd.write("");
       }
       if (lives == 1)
       {
        lcd.write(" ");
       }
       lcd.write(" ");
       start = millis();
       while(millis() - start <= 1000)
       {
         lcd.setRGB(255, 0, 0);
         delay(100);
         lcd.setRGB(255, 255, 255);
         delay(100);
       }
       
    }
}
