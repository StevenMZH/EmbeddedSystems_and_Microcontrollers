const int triggerPin1 = 2;
const int echoPin1 = 8;
const int triggerPin2 = 3;
const int echoPin2 = 9;
const int triggerPin3 = 4;
const int echoPin3 = 10;
const int triggerPin4 = 5;
const int echoPin4 = 11;

const int motorPin = 6;
const int delayTime = 1000;
const int full_distance = 100;
const int empty_distance = 300;

bool full = false;
bool empty = false;

void setup() {
  pinMode(triggerPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(triggerPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(triggerPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  
  pinMode(motorPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int distance1 = calcularDistancia(triggerPin1, echoPin1);
  int distance2 = calcularDistancia(triggerPin2, echoPin2);
  int distance3 = calcularDistancia(triggerPin3, echoPin3);
  int distance4 = calcularDistancia(triggerPin4, echoPin4);
  
  Serial.println("Distancias detectadas (cm):");
  Serial.print("Sensor 1: ");
  Serial.println(distance1);
  Serial.print("Sensor 2: ");
  Serial.println(distance2);
  Serial.print("Sensor 3: ");
  Serial.println(distance3);
  Serial.print("Sensor 4: ");
  Serial.println(distance4);
  Serial.print("\nLlenado: ");
  Serial.println(digitalRead(motorPin));
  Serial.print("\n\n");

  full = (distance1 <= full_distance) && (distance2 <= full_distance) && (distance3 <= full_distance) && (distance4 <= full_distance);
  empty = (distance1 >= empty_distance) || (distance2 >= empty_distance) || (distance3 >= empty_distance) || (distance4 >= empty_distance);
  
  if (empty && !full) {
    digitalWrite(motorPin, HIGH);
  }
  else {
    digitalWrite(motorPin, LOW);
  }

  delay(delayTime);
}

int calcularDistancia(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000); // Espera un máximo de 30 ms para el eco
  
  int distancia = duration * 0.034 / 2;
  return distancia;
}
