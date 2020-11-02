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

//variables
bool start=0, pass;
int choice;
double speedup=1;
unsigned long startedWaiting;
unsigned long wait_time;

// TODO:
// function 2
// function 3
// LCD intigration

void loop()
{
  // non-gameplay behavior
   // display "press button to start!" or some other cheery bs
   // display score (zero or last rounds score)
  if(// button is pressed)
   {
     start=1; // start flag
     score=0;
   }
  while(start==1)
  {
    choice= Random()%3;
    wait_time = 3000*speedup; // base time is 3 seconds (can change with testing)
    switch (choice) 
    {
      case 0:
        pass = push_button();
        break;
      case 1:
        pass =//task 2 function
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
     // displsy "FAIL!" and flash final score
     speedup=1;
     start=0;
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
