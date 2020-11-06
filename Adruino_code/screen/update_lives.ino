// this is a real function that will update the lives counter in 
#include <Wire.h>
#include "DFRobot_RGBLCD.h"

DFRobot_RGBLCD lcd(16,2);  //16 characters and 2 lines of show

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
  
}

void loop() 
{
  lcd.setRGB(255, 255, 255);
  update_lives();
  if (lives == 0)
  {
    delay(2000);
    lives = 3;  
  }
  if (digitalRead(7)==HIGH)
  {
    lives= lives-1;
    while(digitalRead(7)==HIGH)
    {}
  }
}

void update_lives()
{
  switch (lives)
  {
    case 3:
      lcd.setCursor(13, 0);
      lcd.write((unsigned char)0);
      lcd.write((unsigned char)0);
      lcd.write((unsigned char)0);
      break;
    case 2:
      lcd.setCursor(13, 0);
      lcd.write(" ");
      lcd.write((unsigned char)0);
      lcd.write((unsigned char)0);
      break; 
    case 1:
      lcd.setCursor(13, 0);
      lcd.write(" ");
      lcd.write(" ");
      lcd.write((unsigned char)0);
      break;
    case 0:
      lcd.setCursor(13, 0);
      lcd.write(" ");
      lcd.write(" ");
      lcd.write(" ");
      break;          
  } 
}
