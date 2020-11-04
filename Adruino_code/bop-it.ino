// Walter Anderson built the a random seed generator so we could generate a truely randome number
// I basically used his ecaxt code but the origonal can be found here: 
// https://sites.google.com/site/astudyofentropy/project-definition/timer-jitter-entropy-sources/entropy-library/arduino-random-seed

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
 
void setup()
{
  CreateTrulyRandomSeed();
  randomSeed(seed);
  pinMode(7, INPUT); // push button input 
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
int beeps[] = {NOTE_A3, NOTE_B3, NOTE_C3};

// beep durations: 4 = quarter note, 8 = eighth note, etc.:
int beepDurations[] = {4, 4, 4};

// beep setup end

//variables
bool start=0, pass;
int choice;
int lives;
int potpin = A5; // Potentiometer analog pin
double speedup=1;
unsigned long startedWaiting;
unsigned long wait_time;

// TODO:
// function 3
// LCD intigration

void loop()
{
  // non-gameplay behavior
   // display "press button to start!" or some other cheery bs
   // display score (zero or last rounds score)
  if(digitalRead(7)==HIGH)
   {
     start=1; // start flag
     score=0;
     lives=3;
   }
  while(start==1)
  {
    choice= Random()%3;
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
        pass =//task 3 function
       break;   
    }
   if(pass)
   {
     score++;
     // update display with score and "Good!"
     // lower speedup to increase speed
       // NOTE: may not change ever point (ie may change at 5 or 10 point increments)
   }  
  
   else
   {
     // displsy "FAIL!"
     lives = lives-1; // remove a life
     // update lives on display
     if(lives == 0)
     { 
      // flash final score
      speedup=1;
      start=0;
     } 
   }
  }
}
   
bool push_button() {
  startedWaiting = millis(); // get start time
  while(millis() - startedWaiting <= wait_time) // if waitime ammount of time passes
  {
    if (digitalRead(7)==HIGH)
    {
       return true;
    }
  }
  return false;  
}
   
bool pot() {
  startedWaiting = millis();
  while(millis() - startedWaiting <= wait_time)
  {
    if (analogRead(potpin)>=800) // threshold can be altered during testing
    {
       return true;
    }
  }
  return false;  
}

// may be replaced if sound files work
void beeps()
{
 int beepDuration = 1000 / beepDurations[0];
 int pauseBetweenbeeps = beepDuration * 1.30;
 tone(3, melody[choice], beepDuration);
 delay(pauseBetweenbeeps);
 noTone(3);
} 
