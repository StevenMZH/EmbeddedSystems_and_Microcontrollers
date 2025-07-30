bool on = false;
bool max = false;
bool counterClockwise = false;
bool star = false;
bool delta = false;
bool tof = false;

bool timer = false;
bool condition = false;

bool A = false;
bool B = false;
bool C = false;
bool D = false;

bool a,b,c,d;

bool commandSegment = true;
bool timeSegment = false;
bool conditionHeader = false;
bool conditionSegment = false;

bool whileHeader = false; 

int time = 0;
char measurment = 's';
bool timeCondition = false;

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long interval = 1000; //1s

int s = 0;
int m = 0;
int h = 0;

bool* conditions_Var[50];
bool conditions_Gates[50]; 
int condition_VarLine = 0;
int condition_GateLine = 0;

int turningOff_Time = 1000;

// Interpreta cada bit del paquete de datos
void process(uint8_t* package) {

  if(commandSegment){
    on = ((package[0] & 0b10000000) != 0);
    max = ((package[0] & 0b01000000) != 0); 
    counterClockwise = ((package[0] & 0b00100000) != 0);
    star = ((package[0] & 0b00010000) != 0); 
    delta = ((package[0] & 0b00001000) != 0); 
    timer = ((package[0] & 0b00000100) != 0);
    tof = ((package[0] & 0b00000010) != 0); 
    condition = ((package[0] & 0b00000001) != 0); 

    timeSegment = timer;
    conditionSegment = condition; 
    conditionHeader = condition; 
    commandSegment = !(timeSegment || conditionSegment); 

    condition_VarLine = 0;
    condition_GateLine = 0;
  }

  else if(timeSegment){
    
    if((package[0] & 0b10000000) != 0){ measurment = 'h'; }
    else if((package[0] & 0b01000000) != 0){ measurment = 'm'; }
    else{ measurment = 's'; }

    time = (package[0] & 0b00111111);

    setTimer();

    timeSegment = false;
    commandSegment = !(timeSegment || conditionSegment); 
  }

  else if(conditionHeader){
    whileHeader = ((package[0] & 0b00000001) != 0); 
    conditionHeader = false;
  }

  else if(conditionSegment){
    setConditional(package);
  }
}

void clear(int delayTime){
  on = false;
  max = false;
  counterClockwise = false;
  star = false;
  delta = false;
  tof = false;

  timer = false;
  condition = false;

  commandSegment = true;
  timeSegment = false;
  conditionHeader = false;
  conditionSegment = false;
  whileHeader = false; 

  time = 0;
  measurment = 's';
  timeCondition = false;

  currentMillis = 0;
  previousMillis = 0;

  s = 0;
  m = 0;
  h = 0;

  condition_VarLine = 0;
  condition_GateLine = 0;

  reboot(turningOff_Time);
}

void reboot(int delayTime){
    //Apagado para reiniciar proceso
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);

    delay(delayTime);
}

void setMotor(){
    // Actualizar los pines según los valores interpretados
    digitalWrite(2, on ? HIGH : LOW);
    digitalWrite(3, !max && on ? HIGH : LOW);
    digitalWrite(4, max ? HIGH : LOW);
    digitalWrite(5, !counterClockwise && on ? HIGH : LOW);
    digitalWrite(6, counterClockwise ? HIGH : LOW);
    digitalWrite(7, star ? HIGH : LOW);
    digitalWrite(8, delta ? HIGH : LOW);
    digitalWrite(9, timer ? HIGH : LOW);
}

void setTimer(){
  s = 0;
  m = 0;
  h = 0;
    
  if(measurment == 's'){ s = time; }
  else if(measurment == 'm'){ m = time; }
  else if(measurment == 'h'){ h = time; }
  timeCondition = true;

  currentMillis = 0;
  previousMillis = 0;
}

void setConditional(uint8_t* package){
    //IDs
    
    //Inverted
    if((package[0] & 0b00100000) != 0){
      //C,D
      if((package[0] & 0b00010000) != 0){
        if((package[0] & 0b00001000) != 0){ conditions_Var[condition_VarLine] = &d; } //!D
        else{ conditions_Var[condition_VarLine] = &c; } //!C
      }
      //A,B
      else{
        if((package[0] & 0b00001000) != 0){ conditions_Var[condition_VarLine] = &b; } //!B
        else{ conditions_Var[condition_VarLine] = &a; } //!A
      }
    }
    //Normal
    else{
      //C,D
      if((package[0] & 0b00010000) != 0){
        if((package[0] & 0b00001000) != 0){ conditions_Var[condition_VarLine] = &D; } //D
        else{ conditions_Var[condition_VarLine] = &C; } //C
      }
      //A,B
      else{
        if((package[0] & 0b00001000) != 0){ conditions_Var[condition_VarLine] = &B; } //B
        else{ conditions_Var[condition_VarLine] = &A; } //A
      }
      
    }
    condition_VarLine +=1;

    //LogicGate
    if((package[0] & 0b00000100) != 0){
      conditions_Gates[condition_GateLine] = false; //OR
      
      if((package[0] & 0b00000010) != 0){
        conditions_Gates[condition_GateLine] = true; //AND
      } 
      condition_GateLine +=1;
    }

    conditionSegment = ((package[0] & 0b00000001) != 0); 
    commandSegment = !conditionSegment;
}

void runTimer(){
  currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    if (s == 0 && m == 0 && h == 0) {
      if(tof){ 
        timer = false;
        timeCondition = false;
        setMotor(); 
      }
      else{ clear(turningOff_Time); }
      return;

    } else if (s > 0) {
      s--;
    } else if (m > 0) {
      m--; s = 59;
    } else if (h > 0) {
      h--; m = 59; s = 59; 
    }
    
    digitalWrite(9, !digitalRead(9));
  }
}

bool runConditional() {
  bool var = *(conditions_Var[0]);
  bool aux = true;

  int i = 1;
  if(condition_VarLine > 1){
    while(i < condition_VarLine){
      aux = *(conditions_Var[i]);
      if(conditions_Gates[i-1]){ var = var && aux; } 
      else { var = var || aux; }
      i++;
    }
  }
  return var;
}


void setup() {
  // Inicializar los pines
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);

  clear(turningOff_Time);

  Serial.begin(9600); // Iniciar comunicación serial
}

void loop() {
  static bool processed = false; // Bandera para indicar si se ha procesado el último paquete

  //Lectura de Sensores
  A = digitalRead(10); a = !A;
  B = digitalRead(11); b = !B;
  C = digitalRead(12); c = !C;
  D = digitalRead(13); d = !D;
  
  // Si hay suficientes datos disponibles para leer y no se ha procesado el último paquete
  if (Serial.available() >= 1 && !processed) {
    uint8_t package[1]; // Crear un buffer para almacenar el paquete de datos
    Serial.readBytes(package, 1); // Leer el paquete de datos
    
    process(package); // Procesar el paquete de datos
    processed = true; // Establecer la bandera a true para indicar que se ha procesado el paquete
    
    // Si ya termino de leer la instruccion actual:
    if(commandSegment){
        if(on && !tof){ reboot(turningOff_Time); setMotor();}
        else if(on && tof){ reboot(turningOff_Time); }
        else{clear(turningOff_Time);}
    }

  } else if (Serial.available() == 0) {
    processed = false; // Restablecer la bandera si no hay datos disponibles
  }
  
  if(timer && timeCondition && !condition){ runTimer(); }
  if(condition){
    bool expression = runConditional();

    if(whileHeader){
      if(expression){
        if(timer && timeCondition){ setTimer(); }
        runTimer();
      }
      else { 
        reboot(turningOff_Time); 
      }
    }
    else{
      if(expression && timer && timeCondition){ runTimer();}
      if(!expression){ clear(turningOff_Time); }
    }
  }

}


