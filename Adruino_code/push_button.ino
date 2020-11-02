// this is just the push button function, will be put into the  
unsigned long startedWaiting;
unsigned long wait_time; // this will be passed in most likely, just the calced delay
void setup() {
  pinMode(7, INPUT);  
}

bool loop() {
  startedWaiting = millis();
  while(millis() - startedWaiting <= wait_time) // while wait_time ammount of time hasn't passed
  {
    if (digitalRead(7)==HIGH) // if button pushed
    {
       return true; // return true (they passed)
    }
  }
  return false; // if the time passes, they fail
}
