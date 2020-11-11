// prototype for direction testing function
// it just prints a letter to represent which direction the joysrick is facing
#include <Wire.h>
#include "DFRobot_RGBLCD.h"

unsigned long startedWaiting;
unsigned long wait_time; // this will be passed in most likely, just the calced delay
int ypin = A2; // y axis pin
int xpin = A1; // x axit pin
const int colorR = 255;
const int colorG = 255;
const int colorB = 255;

DFRobot_RGBLCD lcd(16,2);

void setup() 
{
  lcd.init();
  lcd.setRGB(colorR, colorG, colorB);  
}

void loop() 
{
  int btop= 1023-150; // high bound number
  int bbot= 150; // low bound number

  lcd.setCursor(0, 0);
  if (analogRead(ypin)< bbot && analogRead(xpin)> bbot && analogRead(xpin)< btop) // low y axis value is up
  {lcd.print("U");}
  else if (analogRead(ypin)> btop && analogRead(xpin)> bbot && analogRead(xpin)< btop) // high y axis value is down
  {lcd.print("D");}
  else if (analogRead(xpin)< bbot && analogRead(ypin)> bbot && analogRead(ypin)< btop) // low x axit value is right
  {lcd.print("R");}
  else if (analogRead(xpin)> btop && analogRead(ypin)> bbot && analogRead(ypin)< btop) // high x axis value is left
  {lcd.print("L");}
}
