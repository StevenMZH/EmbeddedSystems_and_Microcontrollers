bool on = false;
bool max = false;
bool counterClockwise = false;
bool star = false;
bool delta = false;
bool timer = false;
bool tof = false;
bool condition = false;

void process(char* package) {
  // Interpretar cada bit del paquete de datos
  on = package[0] == '1';
  max = package[1] == '1';
  counterClockwise = package[2] == '1';
  star = package[3] == '1';
  delta = package[4] == '1';
  timer = package[5] == '1';
  tof = package[6] == '1';
  condition = package[7] == '1';
  
  // Actualizar los pines según los valores interpretados
  digitalWrite(2, on ? HIGH : LOW);
  digitalWrite(3, max ? HIGH : LOW);
  digitalWrite(4, counterClockwise ? HIGH : LOW);
  digitalWrite(5, star ? HIGH : LOW);
  digitalWrite(6, delta ? HIGH : LOW);
  digitalWrite(7, timer ? HIGH : LOW);
  digitalWrite(8, tof ? HIGH : LOW);
  digitalWrite(9, condition ? HIGH : LOW);
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
  
  Serial.begin(9600); // Iniciar comunicación serial
}

void loop() {
  // Si hay datos disponibles para leer
  if (Serial.available() >= 8) {
    char package[9]; // Crear un buffer para almacenar el paquete de datos
    Serial.readBytes(package, 9); // Leer el paquete de datos
    
    process(package); // Procesar el paquete de datos
  }
}

