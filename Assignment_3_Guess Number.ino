int bitPattern[10] = {B00001000 , B01101110 , B00010100 , B01000100 , B01100010 , B01000001 , B00000001 , B01101100 , B00000000 , B01000000};
int more_or_low[2] = {B00001001 , B00011011};
const int segmentPins[7] = {2, 3, 4, 5, 6, 7,8};
int randomNo,n=0,debounce_delay= 50;
int buttonState[2],lastButtonState[2]= {LOW,LOW}; 
long long int debouce_time[2]= {0,0};

void setup() 
{
  Serial.begin(9600);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  randomSeed(analogRead(A0));
  randomNo= random(1, 10);
  for(int i=0; i<7; i++){
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() 
{
  boolean isBitSet;
  int readingA = digitalRead(10);
  if (readingA != lastButtonState[0]) 
  {
    debouce_time[0]= millis();
  }
  if ((millis()-debouce_time[0]) > debounce_delay) 
  {
    //Serial.println(readingA);
    if (readingA != buttonState[0]) 
    {
      buttonState[0]= readingA;  
      if(buttonState[0] == HIGH)
      {
        n++;
        n%=10;if(n==0){n=1;}
        for (int segment = 0; segment < 7; segment++){  //
          isBitSet= bitRead(bitPattern[n], segment);
          digitalWrite(segmentPins[segment], isBitSet);
        } 
      }
    }
  }
  lastButtonState[0]= readingA;

  int readingB = digitalRead(11);
  if (readingB != lastButtonState[1]) 
  {
    debouce_time[1]= millis();
  }
  if ((millis()   - debouce_time[1]) > debounce_delay) 
  {
    if (readingB != buttonState[1]) 
    {
      buttonState[1]= readingB;  
      if(buttonState[1] == HIGH)
      {
        if(n>randomNo)
        {
          for (int segment = 0; segment < 7; segment++)
          {  
            isBitSet= bitRead(more_or_low[0], segment);
            digitalWrite(segmentPins[segment], isBitSet);  
          } 
        } 
        else if(n<randomNo)
        {
          for (int segment = 0; segment < 7; segment++)
          {  
            isBitSet= bitRead(more_or_low[1], segment);
            digitalWrite(segmentPins[segment], isBitSet);  
          } 
        } 
        else 
        {
          for (int segment = 0; segment < 7; segment++)
          {  
            isBitSet= bitRead(bitPattern[0], segment);
            digitalWrite(segmentPins[segment], isBitSet);  
            randomNo= random(1, 10);
            n=0;
          } 
        }
      }
    }
  }
  lastButtonState[1]= readingB;
}