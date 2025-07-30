
#include <Servo.h>

Servo servo1;

char data = ' ';

int pin = 9;
int maxPulse = 2500;
int minPulse = 500;
int angle = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 2; i <= 9; i++) {
    pinMode(i, OUTPUT);
  }
  
  servo1.attach(pin, minPulse, maxPulse);
}

void loop() {
  if (Serial.available() > 0) {
    data = Serial.read();

    if(data == 'A'){angle = 0; for (int i = 2; i <= 6; i++) { digitalWrite(i, LOW); };  digitalWrite(2, HIGH); servo1.write(angle);}
    else if(data == 'B'){angle = 45; for (int i = 2; i <= 6; i++) { digitalWrite(i, LOW); }; digitalWrite(3, HIGH); servo1.write(angle);}
    else if(data == 'C'){angle = 90; for (int i = 2; i <= 6; i++) { digitalWrite(i, LOW); }; digitalWrite(4, HIGH); servo1.write(angle);}
    else if(data == 'D'){angle = 135; for (int i = 2; i <= 6; i++) { digitalWrite(i, LOW); }; digitalWrite(5, HIGH); servo1.write(angle);}
    else if(data == 'E'){angle = 180; for (int i = 2; i <= 6; i++) { digitalWrite(i, LOW); }; digitalWrite(6, HIGH); servo1.write(angle);}
    delay(100);
  }

}
