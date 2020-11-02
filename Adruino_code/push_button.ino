// this is just the push button function test to verify my code works as intended 
// NOTE: for this code, the button connects high and there is a 100 ohm to ground on the 7 pin
unsigned long startedWaiting;
unsigned long wait_time; // this will be passed in most likely, just the calced delay
void setup() {
  pinMode(7, INPUT);  
  pinMode(8, OUTPUT); // pass condition indicator
  pinMode(4, OUTPUT); // fail condition indicator
}

// the code here runs to false either way after the wait time (3 sec)
// in the real code it will return after pass and fail
// the point of this is to test the timer method and see if pressing the button within the timw
// gets us to out pass condition
void loop() {
  wait_time = 3000;
  startedWaiting = millis();
  while(millis() - startedWaiting <= wait_time)
  {
    if (digitalRead(7)==HIGH)
    {
       //return true;
       digitalWrite(8, HIGH);
    }
  }
  //return false;  
  digitalWrite(4, HIGH);
  delay(3000); 
  digitalWrite(8, LOW);
  digitalWrite(4, LOW);
