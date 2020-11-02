// this is just the potentiometer  function test, will be changed in main  
unsigned long startedWaiting;
unsigned long wait_time; // this will be passed in most likely, just the calced delay
int potpin = A5;
void setup() {  
  pinMode(8, OUTPUT); // pass condition
  pinMode(4, OUTPUT); // fail condition
}

void loop() {
  wait_time = 3000;
  startedWaiting = millis();
  while(millis() - startedWaiting <= wait_time)
  {
    if (analogRead(potpin)>=800) // controls how far the potentiometer has to move 
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
}
