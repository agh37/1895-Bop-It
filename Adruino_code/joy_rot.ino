// detects if the user rotated the joystick in the desired direction
unsigned long startedWaiting;
unsigned long wait_time; // this will be passed in most likely, just the calced delay
int ypin = A2;
int xpin = A1;
void setup() {
  pinMode(8, OUTPUT); // pass condition
  pinMode(4, OUTPUT); 
}

void loop() {
  char seq[4]; // this is where we store our direction sequence
  bool cw=0;
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
   }
   if(count>=4) // one the array is full
   {
    if(cw) // if we are testing for clockwise
    {
      // return true for the clockwise conditions and false for non clockwise conditions
      if((seq[0]=='u'&&seq[1]=='r'&&seq[2]=='d'&&seq[3]=='l')||(seq[0]=='r'&&seq[1]=='d'&&seq[2]=='l'&&seq[3]=='u')||(seq[0]=='d'&&seq[1]=='l'&&seq[2]=='u'&&seq[3]=='r')||(seq[0]=='l'&&seq[1]=='u'&&seq[2]=='r'&&seq[3]=='d'))
      {
        //return true; 
        digitalWrite(8, HIGH);
      }
      else
      {
        //return false;  
        digitalWrite(4, HIGH);
      }
    }
    if(not cw) // its the exact same for counter clockwise as clockwise but for counter clockwise conditions
    {
      if((seq[0]=='u'&&seq[1]=='l'&&seq[2]=='d'&&seq[3]=='r')||(seq[0]=='r'&&seq[1]=='u'&&seq[2]=='l'&&seq[3]=='d')||(seq[0]=='d'&&seq[1]=='r'&&seq[2]=='u'&&seq[3]=='l')||(seq[0]=='l'&&seq[1]=='d'&&seq[2]=='r'&&seq[3]=='u'))
      {
        //return true; 
        digitalWrite(8, HIGH);
      }
      else
      {
        //return false;  
        digitalWrite(4, HIGH);
      }
    }
   }
  }
  //return false;  
  digitalWrite(4, HIGH);
  delay(3000); 
  digitalWrite(8, LOW);
  digitalWrite(4, LOW);
}

char test_dir()
{
  // almost the same as my direction test code but we return chars and a q if the joystick isn't pressed
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
