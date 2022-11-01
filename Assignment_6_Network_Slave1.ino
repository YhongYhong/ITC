//-----------------------Slave-------------------------//

#include <Wire.h>
#define MY_ADDR 8
char empty[10] = "Token#0#";
char format[10] = "Token#1#1#";


char messageR[300];
char temp[300];

int mess = 0;
int lenMessage;


void setup() {
  Serial.begin(9600);
  Wire.begin(MY_ADDR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  delay(500);
}


int regex(){
  if(messageR[0] == '1' || messageR[0] == '0' || messageR[0] == '2'){
    return 1;
  }
  else{
    return 0;
  }
}

void receiveEvent(int howMany) {
  if (Wire.available() > 0) {
    int i = 0;
    while (Wire.available() > 0) {
      messageR[i] = Wire.read();
      i++;
    }
    lenMessage = i;
    messageR[i] = '\0';
    // Serial.println(messageR);
    showMessage();
    if (isEmpty() == 1) {
      getChar();
      if(!regex()){
        setNormal();
      } else {
        setMessage();
      }
      // Serial.println("IsEmpty Okay");
    }
  }
}

void setMessage() {
  for (int i = 0; i < 8; i++) {
    temp[i] = empty[i];
  }
  temp[6] = '1';
  temp[8] = messageR[0];
  temp[9] = '#';
  int i;
  for (i = 10; i < lenMessage + 8; i++) {
    temp[i] = messageR[i - 8];
  }
  temp[i] = '\0';
  for (int j = 0; j < i; j++) {
    messageR[j] = temp[j];
  }
  messageR[i] = '\0';
}

void requestEvent() {
  Wire.write(messageR);
}

void getChar() {
  while (Serial.available() > 0) {
    char inByte = Serial.read();
    if (inByte != '\n') {
      messageR[mess] = (char)inByte;
      mess++;
    } else {
      messageR[mess] = '\0';
      lenMessage = mess;
      mess = 0;
    }
    
  }
  Serial.println(messageR);
}


void showMessage() {
  if (messageR[6] == '1' && messageR[8] == '1') {
    for (int i = 10; i < lenMessage; i++) {

      Serial.print(messageR[i]);
    }
    Serial.println();
    
    setNormal();
  }
}


int isEmpty() {
  for (int i = 0; i < 8; i++) {
    if (messageR[i] != empty[i]) {
      return 0;
      break;
    }
  }
  // Serial.println(void);
  return 1;
}

void setNormal() {
  for (int i = 0; i < 8; i++) {
    messageR[i] = empty[i];
  }
  messageR[8] = '\0';
}

void loop() {
  
}