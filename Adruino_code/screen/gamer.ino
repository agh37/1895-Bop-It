#include <Wire.h>
#include "DFRobot_RGBLCD.h"

 int r = 255;
 int g = 0;
 int b = 0;

DFRobot_RGBLCD lcd(16,2);  //16 characters and 2 lines of show

void setup() {
    // initialize
    lcd.init();
    
    lcd.setRGB(r, g, b);
    
    // Print a message to the LCD.
    lcd.print("hello, world!");

    delay(1000);
}

void loop() 
{
  if(r > 0 && b == 0){
    r--;
    g++;
  }
  if(g > 0 && r == 0){
    g--;
    b++;
  }
  if(b > 0 && g == 0){
    r++;
    b--;
  }
  lcd.setRGB(r, g, b);
  delay(10);
}
