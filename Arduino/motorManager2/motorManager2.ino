bool on = false;
bool max = false;
bool counterClockwise = false;
bool star = false;
bool delta = false;
bool timer = false;
bool tof = false;
bool condition = false;

void process(uint8_t* package) {
  // Interpretar cada bit del paquete de datos
  on = (package[0] & 0b10000000) != 0; // Verifica el bit más significativo
  max = (package[0] & 0b01000000) != 0; // Verifica el segundo bit más significativo
  counterClockwise = (package[0] & 0b00100000) != 0; // Verifica el tercer bit más significativo
  star = (package[0] & 0b00010000) != 0; // Verifica el cuarto bit más significativo
  delta = (package[0] & 0b00001000) != 0; // Verifica el quinto bit más significativo
  timer = (package[0] & 0b00000100) != 0; // Verifica el sexto bit más significativo
  tof = (package[0] & 0b00000010) != 0; // Verifica el séptimo bit más significativo
  condition = (package[0] & 0b00000001) != 0; // Verifica el bit menos significativo
  
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
  static bool processed = false; // Bandera para indicar si se ha procesado el último paquete
  
  // Si hay suficientes datos disponibles para leer y no se ha procesado el último paquete
  if (Serial.available() >= 1 && !processed) {
    uint8_t package[1]; // Crear un buffer para almacenar el paquete de datos
    Serial.readBytes(package, 1); // Leer el paquete de datos
    
    process(package); // Procesar el paquete de datos
    processed = true; // Establecer la bandera a true para indicar que se ha procesado el paquete
  } else if (Serial.available() == 0) {
    processed = false; // Restablecer la bandera si no hay datos disponibles
  }
}
