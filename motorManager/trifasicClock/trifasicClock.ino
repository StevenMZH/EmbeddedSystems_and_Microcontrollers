
//22 times 'time'
void conmutator(int pin1, int pin2, int time){
  digitalWrite( pin1 ,true); digitalWrite( pin2 ,true);
  delay(time);
  digitalWrite( pin1 ,false); digitalWrite( pin2 ,false);
  delay(5 * time);

  digitalWrite( pin1 ,true); digitalWrite( pin2 ,true);
  delay(time);
  digitalWrite( pin1 ,false); digitalWrite( pin2 ,false);
  delay(3 * time);

  digitalWrite( pin1 ,true); digitalWrite( pin2 ,true);
  delay(time);
  digitalWrite( pin1 ,false); digitalWrite( pin2 ,false);

  delay(time);

  digitalWrite( pin1 ,true); digitalWrite( pin2 ,true);
  delay(time);
  digitalWrite( pin1 ,false); digitalWrite( pin2 ,false);

  delay(time);

  digitalWrite( pin1 ,true); digitalWrite( pin2 ,true);
  delay(time);
  digitalWrite( pin1 ,false); digitalWrite( pin2 ,false);

  digitalWrite( pin1 ,true); digitalWrite( pin2 ,true);
  delay(time);
  digitalWrite( pin1 ,false); digitalWrite( pin2 ,false);
  delay(3 * time);

  digitalWrite( pin1 ,true); digitalWrite( pin2 ,true);
  delay(time);
  digitalWrite( pin1 ,false); digitalWrite( pin2 ,false);
  delay(5 * time);
}

void clock(int delayTime){

  digitalWrite( 8, false);
  digitalWrite( 3 ,true); digitalWrite( 4 ,true);
  delay(delayTime);
  
  digitalWrite( 3, false);
  digitalWrite( 4 ,true); digitalWrite( 5 ,true);
  delay(delayTime);
  
  digitalWrite( 4, false);
  digitalWrite( 5, true); digitalWrite( 6 ,true);
  delay(delayTime);
  

  digitalWrite( 5, false);
  digitalWrite( 6 ,true); digitalWrite( 7 ,true);
  delay(delayTime);
  
  digitalWrite( 6, false);
  digitalWrite( 7 ,true); digitalWrite( 8 ,true);
  delay(delayTime);
  
  digitalWrite( 7, false);
  digitalWrite( 8 ,true); digitalWrite( 3 ,true);
  delay(delayTime);
}

//66 times 'time'
void clockV2(int delayTime){
  conmutator(3, 4, 1);
  conmutator(4, 5, 1);
  conmutator(5, 6, 1);

  conmutator(6, 7, 1);
  conmutator(7, 8, 1);
  conmutator(8, 3, 1);
}

void setup() {
  for(int i=3; i<=8; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(2, INPUT);

  for(int i=3; i<=8; i++){
    digitalWrite(i, false);
  }
}

void loop() {
  if(digitalRead(2)){ clock(1); }
  else{ clock(2); }
}
