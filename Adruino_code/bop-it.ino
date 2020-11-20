// Walter Anderson built the a random seed generator so we could generate a truely randome number
// I basically used his ecaxt code but the origonal can be found here: 
// https://sites.google.com/site/astudyofentropy/project-definition/timer-jitter-entropy-sources/entropy-library/arduino-random-seed

#include <Wire.h>
#include "DFRobot_RGBLCD.h"
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/atomic.h>
#define randomSeed(s) srandom(s)
 
volatile uint32_t seed;  // These two variables can be reused in your program after the
volatile int8_t nrot;    // function CreateTrulyRandomSeed()executes in the setup() 
                         // function.
 
void CreateTrulyRandomSeed()
{
  seed = 0;
  nrot = 32; 
  
  // The following five lines of code turn on the watch dog timer interrupt to create the seed value
  cli();                                             
  MCUSR = 0;                                         
  _WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (1<<WDE); 
  _WD_CONTROL_REG = (1<<WDIE);                       
  sei();                                             
 
  while (nrot > 0);  // wait here until seed is created
 
  // The following five lines turn off the watch dog timer interrupt
  cli();                                             
  MCUSR = 0;                                         
  _WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (0<<WDE); 
  _WD_CONTROL_REG = (0<< WDIE);                      
  sei();                                             
}
 
ISR(WDT_vect)
{
  nrot--;
  seed = seed << 8;
  seed = seed ^ TCNT1L;
}

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

DFRobot_RGBLCD lcd(16,2);

void setup()
{
  CreateTrulyRandomSeed();
  randomSeed(seed);
  pinMode(7, INPUT); // push button input 
  pinMode(6, INPUT);
  lcd.init();
  lcd.customSymbol(0, heart);
}

// beep setup start (remove if sound files work) 

// note declaration
// I might not need them all but what if I do?
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// sound groupings for beeps
int beep[] = {NOTE_A3, NOTE_B3, NOTE_C3};

// beep durations: 4 = quarter note, 8 = eighth note, etc.:
int beepDurations[] = {4, 4, 4};

// beep setup end

//variables
bool start=0, pass, dbg=0;
int choice;
int lives;
int potpin = A3; // Potentiometer analog pin
int ypin = A2;
int xpin = A1;
int score= 0;
double speedup=1;
unsigned long double startedWaiting;
unsigned long double wait_time;

// TODO:
// speedup

void loop()
{
  lcd.setRGB(255, 255, 255);
  lcd.setCursor(0, 0);
  lcd.print("Press to start");
  if(digitalRead(7)==HIGH)
   {
     start=1; // start flag
     score=0;
     lives=3;
     speedup=1;
     lcd.setCursor(0, 0);
     lcd.print("              ");
     update_lives();
     update_score();
   }
 if(analogRead(potpin)>=800 && digitalRead(6))
  {
     lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    dbg=1;
    debug(); 
  } 
  while(start==1)
  {
    lcd.setCursor(0, 1);
    lcd.print("   ");
    choice= rand()%3;
    wait_time = 3000*speedup; // base time is 3 seconds (can change with testing)
    beeps();
    switch (choice) 
    {
      case 0:
        pass = push_button();
        break;
      case 1:
        pass = pot();
        break;
      case 2:
        pass =joy_rot();
       break;   
    }
   if(pass)
   {
     score++;
     update_score();
     if (score==99) // if you're out of lives play game over screen snf return to pre-game
     {
        lcd.setCursor(0, 1);
        lcd.print("   ");
        lcd.setRGB(0, 255, 0);
        lcd.setCursor(13, 0);
        lcd.write("   ");
        lcd.setCursor(0, 0);
        lcd.print("YOU WIN!  ");
        start=0;
        delay(3000);
     }
     else
     {
       lcd.setCursor(0, 0);
       lcd.print("GOOD! ");
       startedWaiting = millis();
       while(millis() - startedWaiting <= 1000)
       {
         lcd.setRGB(0, 255, 0);
         delay(100);
         lcd.setRGB(255, 255, 255);
         delay(100);
       }
       // lower speedup to increase speed
       if (score%5==0 && score!=0)
       {
         speedup=speedup-.1;
       }
     }
   }  
  
   else // failed action
   {
       lives= lives-1; // lower lives
       update_lives(); // update lives
       if (lives==0) // if you're out of lives play game over screen snf return to pre-game
       {
        lcd.setCursor(0, 1);
        lcd.print("   ");
        lcd.setRGB(255, 0, 0);
        lcd.setCursor(13, 0);
        lcd.write("   ");
        lcd.setCursor(0, 0);
        lcd.print("YOU LOSE! ");
        start=0;
        delay(3000);
       }
       else // display wrong and flash screen
       {
        lcd.setCursor(0, 0);
        lcd.print("WRONG!");
        startedWaiting = millis();
        while(millis() - startedWaiting <= 1000)
        {
          lcd.setRGB(255, 0, 0);
          delay(100);
          lcd.setRGB(255, 255, 255);
          delay(100);
        }
       } 
    }
  }
}
   
bool push_button() 
{
  bool attop;
  if(analogRead(potpin)>=800)
  {attop=1;}
  else if(analogRead(potpin)<=223)
  {attop=0;}
  lcd.setCursor(0, 0);
  lcd.print("BOP-IT");
  startedWaiting = millis(); // get start time
  while(millis() - startedWaiting <= wait_time) // if waitime ammount of time passes
  {
    if (digitalRead(7)==HIGH)
    {
       return true;
    }
    if (analogRead(potpin)>=800 && not attop ) // threshold can be altered during testing
    {
      return false;
    }
    if (analogRead(potpin)<=223 && attop ) // threshold can be altered during testing
    {
      return false;
    }
    if (test_dir()!='q')
    {
      return false;
    }
  }
  return false;  
}
   
bool pot() 
{
 lcd.setCursor(0, 0);
 lcd.print("SLIDE ");
 bool attop;
 if(analogRead(potpin)>=800)
 {attop=1;}
 else if(analogRead(potpin)<=223)
 {attop=0;}
 else
 {return false;}
  startedWaiting = millis();
  while(millis() - startedWaiting <= wait_time)
  {
    if (analogRead(potpin)>=800 && not attop ) // threshold can be altered during testing
    {
       return true;
    }
    if (analogRead(potpin)<=223 && attop ) // threshold can be altered during testing
    {
       return true;
    }
    if (digitalRead(7)==HIGH)
    {
       return false;
    }
    if (test_dir()!='q')
    {
      return false;
    }
  }
  return false;  
}

bool joy_rot() 
{
  bool attop;
  if(analogRead(potpin)>=800)
  {attop=1;}
  else if(analogRead(potpin)<=223)
  {attop=0;}
  lcd.setCursor(0, 0);
  lcd.print("ROTATE");
  char seq[4]; // this is where we store our direction sequence
  bool cw=rand()%2;
  lcd.setCursor(0, 1);
  if(cw)
  {lcd.print("CW ");} 
  else
  {lcd.print("CCW");}
  for(int i=0;i<4;i++) // filling the array with nothing values
  {
    seq[i]='q';
  }
  wait_time = 3000;
  startedWaiting = millis();
  int count=0; // serves to count how many inputs we've saved and also what element in the sequency array we are filling
  while(millis() - startedWaiting <= wait_time)
  {
   if(count<4) // if the array isn't filled
   {
    seq[count]=test_dir(); // test what direction the joystick is in
    if(seq[count]!='q') // if the function outputs an important value
    {
      if(count==0) // if this is the first element just comit the tested value to the array
      {
        count++;
      }
      else if(seq[count]!= seq[count-1]) // if its not the first value, only comit it if the new element is diffrent than the last element
      {
        count++;
      }
      // if one of those conditions isn't met, we are going to overwrite the value we dont like until they are
    }
     if (analogRead(potpin)>=800 && not attop ) // threshold can be altered during testing
      {
        return false;
      }
      if (analogRead(potpin)<=223 && attop ) // threshold can be altered during testing
      {
        return false;
      }
      if (digitalRead(7)==HIGH)
      {
        return false;
      }
   }
   if(count>=4) // one the array is full
   {
    if(cw) // if we are testing for clockwise
    {
      // return true for the clockwise conditions and false for non clockwise conditions
      if((seq[0]=='u'&&seq[1]=='r'&&seq[2]=='d'&&seq[3]=='l')||(seq[0]=='r'&&seq[1]=='d'&&seq[2]=='l'&&seq[3]=='u')||(seq[0]=='d'&&seq[1]=='l'&&seq[2]=='u'&&seq[3]=='r')||(seq[0]=='l'&&seq[1]=='u'&&seq[2]=='r'&&seq[3]=='d'))
      {
        return true; 
      }
      else
      {
        return false;  
      }
    }
    if(not cw) // its the exact same for counter clockwise as clockwise but for counter clockwise conditions
    {
      if((seq[0]=='u'&&seq[1]=='l'&&seq[2]=='d'&&seq[3]=='r')||(seq[0]=='r'&&seq[1]=='u'&&seq[2]=='l'&&seq[3]=='d')||(seq[0]=='d'&&seq[1]=='r'&&seq[2]=='u'&&seq[3]=='l')||(seq[0]=='l'&&seq[1]=='d'&&seq[2]=='r'&&seq[3]=='u'))
      {
        return true; 
      }
      else
      {
        return false;  
      }
    }
   }
  }
  return false;  
}
// direction test for my rotate function
char test_dir()
{
  int btop= 1023-150;
  int bbot= 150;

  if (analogRead(ypin)< bbot && analogRead(xpin)> bbot && analogRead(xpin)< btop)
  {return 'u';}
  else if (analogRead(ypin)> btop && analogRead(xpin)> bbot && analogRead(xpin)< btop)
  {return 'd';}
  else if (analogRead(xpin)< bbot && analogRead(ypin)> bbot && analogRead(ypin)< btop)
  {return 'r';}
  else if (analogRead(xpin)> btop && analogRead(ypin)> bbot && analogRead(ypin)< btop)
  {return 'l';}
  else
  {return 'q';}
}

// may be replaced if sound files work
void beeps()
{
 int beepDuration = 1000 / beepDurations[0];
 int pauseBetweenbeeps = beepDuration * 1.30;
 tone(3, beep[choice], beepDuration);
 delay(pauseBetweenbeeps);
 noTone(3);
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
void update_score()
{
  lcd.setCursor(14, 1);
  if(score<10)
  {lcd.print("0");}
  lcd.print(score);
}

void debug()
{
 while(dbg)
 { 
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
  if(analogRead(potpin)>=800 && digitalRead(6))
  {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    dbg=0;
    debug(); 
  } 
 }
} 
