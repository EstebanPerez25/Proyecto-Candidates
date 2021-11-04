
#include "Zonas.h"

byte mc;                    //Variable de control de zonas

//Objeto para las zonas
zonas zona;

void setup() {
  Serial.begin(115200);
  mc = 0;    //Cambiar a 1 luego de calibracion
}


void loop() {
  if (mc == 0)
  {
    zona.calibrar();
    do{zona.test();}while(true);
  }

  //Inicio de Zona A
  if (mc == 1)
  {
    zona.zonaA();
    mc = 2;
  }


  //Inicio de Zona B
  if (mc == 2)
  {
    zona.zonaB();
    mc = 3;
  }


  //Inicio de Zona C
  if (mc == 3)
  {
    zona.zonaC();
    mc = 4;
  }


  //Inicio Rampa
  if (mc == 4)
  {
    zona.rampa();
    mc = 5;
  }
}


