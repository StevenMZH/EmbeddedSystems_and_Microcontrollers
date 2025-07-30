int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;

int pinE = 6;
int pinF = 7;
int pinG = 8;

int display1_earth = 9;
int display2_earth = 10;

int magneticLocker = 11;

int refreshFrame_Time = 10;
int refreshImage_Time = 2000;

int unlock_Time = 3000;
int open_Time = 6000;

bool open = false;

struct display{
   bool a;
   bool b;
   bool c;
   bool d;

   bool e;
   bool f;
   bool g;
};

struct display dC = {true,false,false,true, true,true,false};
struct display dL = {false,false,false,true, true,true,false};
struct display dE = {true,false,false,true, true,true,true};
struct display dP = {true,true,false,false, true,true,true};
struct display dO = {true, true, true, true, true, true, false};
struct display dD = {false, true, true, true, true, false, true};
struct display dS = {true, false, true, true, false, true, true};
struct display dN = {false, false, true, false, true, false, true};

struct display emptyness = {false,false,false,false, false,false,false};


void displayData(struct display data){
  digitalWrite(pinA, data.a ? HIGH : LOW);
  digitalWrite(pinB, data.b ? HIGH : LOW);
  digitalWrite(pinC, data.c ? HIGH : LOW);
  digitalWrite(pinD, data.d ? HIGH : LOW);

  digitalWrite(pinE, data.e ? HIGH : LOW);
  digitalWrite(pinF, data.f ? HIGH : LOW);
  digitalWrite(pinG, data.g ? HIGH : LOW);
}

void displayFrames(int ms, struct display d1, struct display d2){
  int frames = (ms / refreshFrame_Time);

  for(int i=0; i<(frames/2) ; i++){
    digitalWrite(display1_earth, LOW);
    digitalWrite(display2_earth, HIGH);
    displayData(d1);

    readSensors();
    delay(refreshFrame_Time);
    readSensors();

    digitalWrite(display1_earth, HIGH);
    digitalWrite(display2_earth, LOW);
    displayData(d2);

    readSensors();
    delay(refreshFrame_Time);
    readSensors();
  }
}

void displayOpen(){
  int ms = 0;
  digitalWrite(magneticLocker, HIGH);

  while( ms < open_Time ){
    displayFrames(refreshImage_Time, dO, dP); 
    ms+= refreshImage_Time; if(ms >= open_Time){ break; } else if(ms >= unlock_Time){ digitalWrite(magneticLocker, LOW); };

    displayFrames(refreshImage_Time, dP, dE);
    ms+= refreshImage_Time; if(ms >= open_Time){ break; } else if(ms >= unlock_Time){ digitalWrite(magneticLocker, LOW); };

    displayFrames(refreshImage_Time, dE, dN);
    ms+= refreshImage_Time; if(ms >= open_Time){ break; } else if(ms >= unlock_Time){ digitalWrite(magneticLocker, LOW); };

    displayFrames(refreshImage_Time, dN, dO);
    ms+= refreshImage_Time; if(ms >= unlock_Time){ digitalWrite(magneticLocker, LOW); };  
    open = false;
  }
}

void displayClosed(){

  displayFrames(refreshImage_Time, dC, dL); if(open){return;}
  displayFrames(refreshImage_Time, dL, dO); if(open){return;}
  displayFrames(refreshImage_Time, dO, dS); if(open){return;}
  displayFrames(refreshImage_Time, dS, dE); if(open){return;}
  displayFrames(refreshImage_Time, dE, dD); if(open){return;}
  displayFrames(refreshImage_Time, dD, dC); if(open){return;}
}

void setup() {
  Serial.begin(9600);
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  displayData(emptyness);
}

void readSensors(){
  if(digitalRead(A0) || digitalRead(A1) || digitalRead(A2)){ Serial.print("0"); }
  
  digitalWrite(11, digitalRead(A0) ? HIGH : LOW);
  digitalWrite(12, digitalRead(A1) ? HIGH : LOW);
  digitalWrite(13, digitalRead(A2) ? HIGH : LOW);
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();
    
    if (data == '1') {
      open = true;
    }
    else if (data == '0') {
      open = false;
    }
  }


  if (open){ displayOpen(); }
  else{ displayClosed(); }
  
}

