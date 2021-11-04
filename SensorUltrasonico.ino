#include "SensorUltrasonico.h"

///////////////////////////////////////////////////////CONTRUCTOR
sensorUltrasonico::sensorUltrasonico(byte trig, byte echo) {

  _trig = trig;
  _echo = echo;

  //Pines UltrasÃ³nico
  pinMode(_trig, OUTPUT);
  pinMode(_echo, INPUT);
}

///////////////////////////////////////////////////////MÃ‰TODOS
float sensorUltrasonico::distancia() {
  digitalWrite(_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trig, LOW);

  _duracion = pulseIn(_echo, HIGH);
  dist = (_duracion / 2) / 29;        //Esta variable corresponde a la distancia registrada por el sensor
  return dist;

}


