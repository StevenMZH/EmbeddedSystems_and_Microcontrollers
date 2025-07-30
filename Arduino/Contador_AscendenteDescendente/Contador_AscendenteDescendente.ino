// Definir los pines para cada segmento del display de 7 segmentos
const int segmentos[7] = {2, 3, 4, 5, 6, 7, 8};

// Definir los pines para cada dígito del display de 7 segmentos
const int digitos[2] = {9, 10};

// Definir los patrones para cada dígito del display de 7 segmentos (0-9)
const byte patrones[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

void setup() {
  // Configurar los pines de los segmentos como salidas
  for (int i = 0; i < 7; i++) {
    pinMode(segmentos[i], OUTPUT);
  }
  
  // Configurar los pines de los dígitos como salidas
  for (int i = 0; i < 2; i++) {
    pinMode(digitos[i], OUTPUT);
  }
}

void loop() {
  // Contador ascendente
  for (int num = 0; num < 100; num++) {
    int decenas = num / 10;
    int unidades = num % 10;
    mostrarNumero(decenas, unidades);
  }

  // Contador descendente
  for (int num = 99; num >= 0; num--) {
    int decenas = num / 10;
    int unidades = num % 10;
    mostrarNumero(decenas, unidades);
  }
}

void mostrarNumero(int decenas, int unidades) {
  for (int num = 0; num < 10; num++){
    // Mostrar las decenas
    digitalWrite(digitos[0], LOW); // Encender el primer dígito
    digitalWrite(digitos[1], HIGH); // Apagar el segundo dígito
    mostrarDigito(decenas); // Mostrar las decenas
    delay(5);
    
    // Mostrar las unidades
    digitalWrite(digitos[0], HIGH); // Apagar el primer dígito
    digitalWrite(digitos[1], LOW); // Encender el segundo dígito
    mostrarDigito(unidades); // Mostrar las unidades
    delay(5);
  }
}

void mostrarDigito(int numero) {
  for (int i = 0; i < 7; i++) {
    if (bitRead(patrones[numero], i)) {
      digitalWrite(segmentos[i], HIGH); // Encender el segmento
    } else {
      digitalWrite(segmentos[i], LOW); // Apagar el segmento
    }
  }
}

