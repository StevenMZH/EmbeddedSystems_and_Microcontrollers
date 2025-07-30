
int openningPassword[6] = {1,1,1,1,1,1};
int clossingPassword[6] = {2,2,2,2,2,2};

int actualNum[6] = {0, 0, 0, 0, 0, 0};
int keyCounter = 0;

bool passwordSelector = true;
int failCounter = 0;

bool sensorSwitch = true;

bool isEqual(const int* a, const int* b){
  for(int i = 0; i<6; i++){
    if(a[i] != b[i]){return false;}
  }
  return true;
}

void checkPassword(){

  if(passwordSelector){
    if( isEqual(openningPassword, actualNum) ){
      //Serial.print("  Entry Accepted.  ");
      Serial.print("1");
      passwordSelector = ! passwordSelector;
      digitalWrite(9,LOW);
      failCounter = 0;
      sensorSwitch = false;
    }
    else{
      failCounter += 1;
      //Serial.print("  Entry Denied  ");
      //Serial.print("  Fail Counter: ");
      //Serial.print(failCounter);
      //Serial.print("  ");
    }
  }
  else if( isEqual(clossingPassword, actualNum) ){
    //Serial.print("  Exit Accepted  ");
    passwordSelector = ! passwordSelector;
    digitalWrite(9,HIGH);
    failCounter = 0;
    sensorSwitch = true;
    Serial.print("0");
  }
  else{ 
    failCounter += 1; 
    //Serial.print("  Exit Denied  ");
    //Serial.print("  Fail Counter: ");
    //Serial.print(failCounter);
    //Serial.print("  ");
  }
  
  actualNum[0] = 0; actualNum[1] = 0; actualNum[2] = 0; actualNum[3] = 0; actualNum[4] = 0; actualNum[5] = 0;
  keyCounter = 0;
}

void getKey(){

  if(keyCounter == 6){
    if(digitalRead(5) && digitalRead(8)){
      checkPassword();
    }
    else if(digitalRead(5) && digitalRead(6)){
      actualNum[keyCounter] = 0;
      keyCounter--;
    }
  }
  else{
    //R1
    if(digitalRead(2)){
      //C1
      if(digitalRead(6)){
        actualNum[keyCounter] = 1;
        keyCounter++;
      }
      //C2
      else if(digitalRead(7)){
        actualNum[keyCounter] = 2;
        keyCounter++;
      }
      //C3
      else if(digitalRead(8)){
        actualNum[keyCounter] = 3;
        keyCounter++;
      }
    }

    //R2
    if(digitalRead(3)){
      //C1
      if(digitalRead(6)){
        actualNum[keyCounter] = 4;
        keyCounter++;
      }
      //C2
      else if(digitalRead(7)){
        actualNum[keyCounter] = 5;
        keyCounter++;
      }
      //C3
      else if(digitalRead(8)){
        actualNum[keyCounter] = 6;
        keyCounter++;
      }
    }  
    
    //R3
    if(digitalRead(4)){
      //C1
      if(digitalRead(6)){
        actualNum[keyCounter] = 7;
        keyCounter++;
      }
      //C2
      else if(digitalRead(7)){
        actualNum[keyCounter] = 8;
        keyCounter++;
      }
      //C3
      else if(digitalRead(8)){
        actualNum[keyCounter] = 9;
        keyCounter++;
      }
    }  

    //R4
    if(digitalRead(5)){
      //C1
      if(digitalRead(6) && keyCounter >= 0){
        actualNum[keyCounter] = 0;
        keyCounter--;
      }
      //C2
      else if(digitalRead(7)){
        actualNum[keyCounter] = 0;
        keyCounter++;
      }
      //C3
      else if(digitalRead(8)){
        checkPassword();
      }
    }  
  }

  //print Keys
  if( digitalRead(2) || digitalRead(3) || digitalRead(4) || digitalRead(5) ){

    //Serial.print(actualNum[0]);
    //Serial.print(actualNum[1]);
    //Serial.print(actualNum[2]);
    //Serial.print(" ");
    //Serial.print(actualNum[3]);
    //Serial.print(actualNum[4]);
    //Serial.print(actualNum[5]);
    //Serial.print("  ");
    //delay(200);
  }

}


void setup() {
    Serial.begin(9600);
    for (int i = 2; i <= 10; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(11, INPUT);
  digitalWrite(9,HIGH);
}

void loop() {
    if (Serial.available() > 0) {
    char data = Serial.read();
    
    if (data == '0') {
      failCounter = 3;
    }
  }

  if( digitalRead(11) ){
    failCounter = 0;
    digitalWrite(10, LOW);
  }

  if( (failCounter >= 3) ){
    digitalWrite(10, HIGH);
  }
  else{
    getKey();
  }
}
