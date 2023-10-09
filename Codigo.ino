#include <Servo.h>
//VARIABLES DEL SERVO MOTOR
Servo servo1;
int pinservo = 8;
int pmin = 1000;
int pmax = 2000;
//VARIABLES DEL BOTON
int botonviejo = 1;
int interruptor = A0;
int botonvalor = 0;
int aux = 3;
int botonnuevo;
//VARIABLES DE LOS LEDS
int ledverde1 = 2;
int ledrojo1 = 3;

int ledverde2 = 4;
int ledrojo2 = 5;

int ledverde3 = 6;
int ledrojo3 = 7;

//VARIABLES DEL FOTORESISTOR
int pinentrada1 = A5;
int valorresistensia1;

int pinentrada2 = A4;
int valorresistensia2;

int pinentrada3 = A3;
int valorresistensia3;

int disponible;
int contador;
void setup() {
  Serial.begin(9600);
  //FOTORESISTOR
  pinMode(pinentrada1, INPUT);
  pinMode(pinentrada2, INPUT);
  pinMode(pinentrada3, INPUT);
  //SALIDAS DE LOS LEDS
  pinMode(ledverde1, OUTPUT);
  pinMode(ledrojo1, OUTPUT);

  pinMode(ledverde2, OUTPUT);
  pinMode(ledrojo2, OUTPUT);

  pinMode(ledverde3, OUTPUT);
  pinMode(ledrojo3, OUTPUT);

  //SERVOMOTOR
  servo1.attach(pinservo, pmin, pmax);
  //ENTRADA DEL INTERRUPTOR
  pinMode(interruptor, INPUT);
}

void loop() {
  //ENTRADA MEDICION FOTORESISTOR
  valorresistensia1 = analogRead(pinentrada1);
  valorresistensia2 = analogRead(pinentrada2);
  valorresistensia3 = analogRead(pinentrada3);

  //INTERRUPTOR PARA EL SERVOMOTOR
  botonnuevo = digitalRead(interruptor);
  delay(100);
  if (valorresistensia1 <= 100 || 
      valorresistensia2 <= 100 || 
      valorresistensia3 <= 100) 
     {
    if (botonnuevo == 0 && botonviejo == 1) 
    {
      if (botonvalor == 0) {
        digitalWrite(aux, 1);
        botonvalor = 1;
        servo1.write(180);
      } else {
        digitalWrite(aux, 0);
        botonvalor = 0;
        servo1.write(0);
      }
    }
  }
  botonviejo = botonnuevo;













  //LOGICA PARA EL FOTORESISTEOR
  // Y LOS LEDS
  if (valorresistensia1 <= 100) {
    digitalWrite(ledverde1, LOW);
    digitalWrite(ledrojo1, HIGH);

  } else {
    digitalWrite(ledverde1, HIGH);
    digitalWrite(ledrojo1, LOW);
  }
  if (valorresistensia2 <= 100) {
    digitalWrite(ledverde2, LOW);
    digitalWrite(ledrojo2, HIGH);

  } else {
    digitalWrite(ledverde2, HIGH);
    digitalWrite(ledrojo2, LOW);
  }
  if (valorresistensia3 <= 100) {
    digitalWrite(ledverde3, LOW);
    digitalWrite(ledrojo3, HIGH);

  } else {
    digitalWrite(ledverde3, HIGH);
    digitalWrite(ledrojo3, LOW);
  }

  //monitoreo de disponibilidad
  disponible = valorresistensia1 
             + valorresistensia2 
             + valorresistensia3;

  if (disponible <= 300) {
    contador = 3;
  }

  if (disponible >= 400) {
    contador = 2;
  }

  if (disponible >= 950 && contador == 2) {
    contador = 1;
  }

  if (disponible >= 2000 && contador == 1) {
    contador = 0;
  }

  Serial.println(contador);
}