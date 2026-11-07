// Carrito Bluetooth - Arduino Uno + L298N + HC-05
// App Android: "Arduino Bluetooth RC Car"

#include <SoftwareSerial.h>

// Bluetooth HC-05: TXD del modulo -> pin 2 del Arduino
SoftwareSerial bt(2, 3); // RX, TX

// L298N
const int ENA = 5;   // velocidad motores izquierdos
const int IN1 = 7;
const int IN2 = 8;
const int IN3 = 9;
const int IN4 = 10;
const int ENB = 6;   // velocidad motores derechos

int velocidad = 200; // 0 a 255

// Si al ir hacia adelante un lado gira al reves, cambia su valor a true
const bool INVERTIR_IZQ = false;
const bool INVERTIR_DER = false;

void lado(int en, int a, int b, int v, bool invertir) {
  if (invertir) v = -v;
  if (v > 0) {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
  } else if (v < 0) {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
  } else {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
  }
  analogWrite(en, abs(v));
}

void mover(int izq, int der) {
  lado(ENA, IN1, IN2, izq, INVERTIR_IZQ);
  lado(ENB, IN3, IN4, der, INVERTIR_DER);
}

void procesar(char c) {
  int v = velocidad;
  switch (c) {
    case 'F': mover(v, v); break;           // adelante
    case 'B': mover(-v, -v); break;         // atras
    case 'L': mover(-v, v); break;          // girar izquierda
    case 'R': mover(v, -v); break;          // girar derecha
    case 'G': mover(v / 2, v); break;       // adelante-izquierda
    case 'I': mover(v, v / 2); break;       // adelante-derecha
    case 'H': mover(-v / 2, -v); break;     // atras-izquierda
    case 'J': mover(-v, -v / 2); break;     // atras-derecha
    case 'S': mover(0, 0); break;           // alto
    case 'q': velocidad = 255; break;       // velocidad maxima
    default:
      if (c >= '0' && c <= '9') {
        velocidad = map(c - '0', 0, 9, 90, 240);
      }
      break;
  }
}

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  mover(0, 0);

  Serial.begin(9600); // para probar desde el Monitor Serie
  bt.begin(9600);     // velocidad de fabrica del HC-05
  Serial.println("Carrito listo");
}

void loop() {
  if (bt.available()) {
    char c = bt.read();
    Serial.println(c);
    procesar(c);
  }
  if (Serial.available()) {
    procesar(Serial.read());
  }
}
