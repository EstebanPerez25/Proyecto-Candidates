#include "SensorColor.h"
#include "LedRGB.h"

int _p[3];                      //Valor r, g b cuando el sensor mide

///////////////////////////////////////////////////////CONTRUCTOR
sensorColor::sensorColor(byte s2, byte s3, byte out,bool n) {

  _s2 = s2;
  _s3 = s3;
  _out = out;

  if (n==0){
    colores[8][3]=coloresI[8][3];
  }
  else{
    colores[8][3]=coloresD[8][3];
  }


  Serial.setTimeout(50); //Para sensor de color

  pinMode(_s2, OUTPUT);
  pinMode(_s3, OUTPUT);
  pinMode(_out, INPUT);


}


///////////////////////////////////////////////////////MÃ‰TODOS
int sensorColor::valoresRGB() {

  Serial.println("Escribe la inicial del color (p=rosa, y= amarillo, z= desplegar matriz)");

  while (coloresI[0][2] == 0 || coloresI[1][2] == 0 || coloresI[2][2] == 0 || coloresI[3][2] == 0 || coloresI[4][2] == 0 || coloresI[5][2] == 0 || coloresI[6][2] == 0 || coloresI[7][2] == 0)   {
    if (Serial.available())
    {
      char data = Serial.read();
      if ((data >= 'A'  && data <= 'Z') || (data >= 'a' && data <= 'z'))
      {
        int rangos[2];
        switch (data) {
          case 'b':
            promedios(  _s2,   _s3,   _out);
            Serial.println("");
            Serial.print("Blanco: ");
            coloresI[0][0] = _p[0];
            Serial.print(coloresI[0][0]); Serial.print("-");
            coloresI[0][1] = _p[1];
            Serial.print(coloresI[0][1]); Serial.print("-");
            coloresI[0][2] = _p[2];
            Serial.println(coloresI[0][2]);
            break;

          case 'y':
            promedios(  _s2,   _s3,   _out);
            Serial.println("");
            Serial.print("Amarillo: ");
            coloresI[1][0] = _p[0];
            Serial.print(coloresI[1][0]); Serial.print("-");
            coloresI[1][1] = _p[1];
            Serial.print(coloresI[1][1]); Serial.print("-");
            coloresI[1][2] = _p[2];
            Serial.println(coloresI[1][2]);
            break;

          case 'r':
            promedios(  _s2,   _s3,   _out);
            Serial.println("");
            Serial.print("Rojo: ");
            coloresI[2][0] = _p[0];
            Serial.print(coloresI[2][0]); Serial.print("-");
            coloresI[2][1] = _p[1];
            Serial.print(coloresI[2][1]); Serial.print("-");
            coloresI[2][2] = _p[2];
            Serial.println(coloresI[2][2]);
            break;

          case 'a':
            promedios(  _s2,   _s3,   _out);
            Serial.println("");
            Serial.print("Azul: ");
            coloresI[3][0] = _p[0];
            Serial.print(coloresI[3][0]); Serial.print("-");
            coloresI[3][1] = _p[1];
            Serial.print(coloresI[3][1]); Serial.print("-");
            coloresI[3][2] = _p[2];
            Serial.println(coloresI[3][2]);
            break;

          case 'v':
            promedios(  _s2,   _s3,   _out);
            Serial.println("");
            Serial.print("Verde: ");
            coloresI[4][0] = _p[0];
            Serial.print(coloresI[4][0]); Serial.print("-");
            coloresI[4][1] = _p[1];
            Serial.print(coloresI[4][1]); Serial.print("-");
            coloresI[4][2] = _p[2];
            Serial.println(coloresI[4][2]);
            break;

          case 'm':
            promedios(  _s2,   _s3,   _out);
            Serial.println("");
            Serial.print("Morado: ");
            coloresI[5][0] = _p[0];
            Serial.print(coloresI[5][0]); Serial.print("-");
            coloresI[5][1] = _p[1];
            Serial.print(coloresI[5][1]); Serial.print("-");
            coloresI[5][2] = _p[2];
            Serial.println(coloresI[5][2]);
            break;

          case 'n':
            promedios(  _s2,   _s3,   _out);
            Serial.println("");
            Serial.print("Negro: ");
            coloresI[6][0] = _p[0];
            Serial.print(coloresI[6][0]); Serial.print("-");
            coloresI[6][1] = _p[1];
            Serial.print(coloresI[6][1]); Serial.print("-");
            coloresI[6][2] = _p[2];
            Serial.println(coloresI[6][2]);
            break;

          case 'p':
            promedios(  _s2,   _s3,   _out);
            Serial.println("");
            Serial.print("Rosa: ");
            coloresI[7][0] = _p[0];
            Serial.print(coloresI[7][0]); Serial.print("-");
            coloresI[7][1] = _p[1];
            Serial.print(coloresI[7][1]); Serial.print("-");
            coloresI[7][2] = _p[2];
            Serial.println(coloresI[7][2]);
            break;

          case 'z':
            Serial.println(""); Serial.println("MATRIZ VALORES DE _colores");
            for (int k = 0; k < 8; k++) {
              for (int l = 0; l < 3; l++) {
                Serial.print(coloresI[k][l]); Serial.print(" ");
              }
              Serial.println("");
            }
            break;
        }
      }
    }
  }
  Serial.println("LECTURA DE VALORES COMPLETA"); Serial.println("");
  for (int k = 0; k < 8; k++) {
    for (int l = 0; l < 3; l++) {
      Serial.print(coloresI[k][l]); Serial.print(" ");
    }
    Serial.println("");
  }


  
  return ;
}//Fin valoresRGB



//Imprime la matriz con los valores r g b de cada color
void sensorColor::imprimeMatriz() {
  Serial.println("--------------------------------");
  for (int k = 0; k < 8; k++) {
    for (int l = 0; l < 3; l++) {
      Serial.print(colores[k][l]); Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.println("--------------------------------");
}





// Ã‰ste mÃ©todo lee e IDENTIFICA el color detectado por el sensor
int sensorColor::getColor() {


    /*
    colores[0][0]       //Blanco
    colores[1][0]        //Amarillo
    colores[2][0]     //Rojo
    colores[3][0]    //Azul
    colores[4][0]     //Verde
    colores[5][0]       //Morado
    colores[6][0]       //Negro
    colores[7][0]        //Rosa
  */



  /*Margen que se le agrega al promedio de cada valor rgb para hacer un rango (Si los valores al calibrar son
    muy altos y variados (poca luz, con soporte del robot), poner margen arriba de 10. Si son pequeÃ±os y
    muy semejantes (mucha luz) poner cercanos a 1)*/
#define mg 30
#define s 5       //cantidad de veces que debe ser identificado un color para enviarlo al Main

  //Proceso para identificar al color
  int suma[8] = {0, 0, 0, 0, 0, 0, 0};
  colorRegistrado = 99;


  while (colorRegistrado == 99) {

    //Inicia la lectura para encontrar quÃ© color es
    int r = lecturaRojo(_s2, _s3, _out);
    //delay(50); //por defecto es 250
    int v = lecturaVerde(_s2, _s3, _out);
    //delay(50);
    int a = lecturaAzul(_s2, _s3, _out);
    //delay(50);


    if ((r > colores[0][0] - mg) && (r < colores[0][0] + mg) && (v > colores[0][1] - mg) && (v < colores[0][1] + mg) && (a > colores[0][2] - mg) && (a < colores[0][2] + mg)) {
      //Serial.println("**BLANCO**");
      suma[0] += 1;
      if (suma[0] == s) {
        colorRegistrado =  0;
        Serial.println("0");
        return 0;
      }
    }

    else if ((r > colores[1][0] - mg) && (r < colores[1][0] + mg) && (v > colores[1][1] - mg) && (v < colores[1][1] + mg) && (a > colores[1][2] - mg) && (a < colores[1][2] + mg)) {
      //Serial.println("**AMARILLO**");
      suma[1] += 1;
      if (suma[1] == s) {
        colorRegistrado = 1;
        Serial.println("1");
        return 1;
      }
    }

    else if ((r > colores[2][0] - mg) && (r < colores[2][0] + mg) && (v > colores[2][1] - mg) && (v < colores[2][1] + mg) && (a > colores[2][2] - mg) && (a < colores[2][2] + mg)) {
      //Serial.println("**ROJO**");
      suma[2] += 1;
      if (suma[2] == s) {
        colorRegistrado = 2;
        Serial.println("2");
        return 2;
      }
    }

    else if ((r > colores[3][0] - mg) && (r < colores[3][0] + mg) && (v > colores[3][1] - mg) && (v < colores[3][1] + mg) && (a > colores[3][2] - mg) && (a < colores[3][2] + mg)) {
      //Serial.println("**AZUL**");
      suma[3] += 1;
      if (suma[3] == s) {
        colorRegistrado = 3;
        Serial.println("3");
        return 3;
      }
    }

    else if ((r > colores[4][0] - mg) && (r < colores[4][0] + mg) && (v > colores[4][1] - mg) && (v < colores[4][1] + mg) && (a > colores[4][2] - mg) && (a < colores[4][2] + mg)) {
      //Serial.println("**VERDE**");
      suma[4] += 1;
      if (suma[4] == s) {
        colorRegistrado =  4;
        Serial.println("4");
        return 4;
      }
    }

    else if ((r > colores[5][0] - mg) && (r < colores[5][0] + mg) && (v > colores[5][1] - mg) && (v < colores[5][1] + mg) && (a > colores[5][2] - mg) && (a < colores[5][2] + mg)) {
      //Serial.println("**MORADO**");
      suma[5] += 1;
      if (suma[5] == s) {
        colorRegistrado =  5;
        Serial.println("5");
        return 5;
      }
    }


    else if ((r > colores[6][0] - mg) && (r < colores[6][0] + mg) && (v > colores[6][1] - mg) && (v < colores[6][1] + mg) && (a > colores[6][2] - mg) && (a < colores[6][2] + mg)) {
      //Serial.println("**NEGRO**");
      suma[6] += 1;
      if (suma[6] == s) {
        colorRegistrado =  6;
        Serial.println("6");
        return 6;
      }
    }

    else if ((r > colores[7][0] - mg) && (r < colores[7][0] + mg) && (v > colores[7][1] - mg) && (v < colores[7][1] + mg) && (a > colores[7][2] - mg) && (a < colores[7][2] + mg)) {
      //Serial.println("**ROSA**");
      suma[7] += 1;
      if (suma[7] == s) {
        colorRegistrado = 7;
        Serial.println("7");
        return 7;
      }
    }

    else {
      //Serial.println("NONE");

    }
  }
}


///////////////////////////////////////////////////////////////FUNCIONES NECESARIAS PARA MÃ‰TODOS
//Calcular promedio de los valores registrados para cada color
int promedios(byte _s2, byte _s3, byte  _out) {

  int suma_R = 0;
  int suma_G = 0;
  int suma_B = 0;


  for (int i = 0; i < 5 ; i++) {
    //Lectura de valores
    int rojo = lecturaRojo(_s2, _s3, _out);
    Serial.print(rojo); Serial.print("-");
    delay(150);
    int verde = lecturaVerde(_s2, _s3, _out);
    Serial.print(verde); Serial.print("-");
    delay(150);
    int azul = lecturaAzul(_s2, _s3, _out);
    Serial.println(azul);
    delay(150);

    suma_R += rojo;
    suma_G += verde;
    suma_B += azul;

  }
  //Serial.println("SUMAS"); Serial.print(suma_R); Serial.print("-"); Serial.print(suma_G); Serial.print("-"); Serial.println(suma_B);
  _p[0] = (suma_R / 5);
  _p[1] = (suma_G / 5);
  _p[2] = (suma_B / 5);
  //Serial.println("PROMEDIOS"); Serial.print(_p[0]); Serial.print("-"); Serial.print(_p[1]); Serial.print("-"); Serial.println(_p[2]);
}


//////////Lectura de cada color
int lecturaRojo(byte _s2, byte  _s3, byte  _out) {
  digitalWrite(_s2, 0);
  digitalWrite(_s3, 0);
  int rojo = pulseIn(_out, LOW);
  return rojo;
}
int lecturaVerde(byte _s2, byte  _s3, byte  _out) {
  digitalWrite(_s2, 1);
  digitalWrite(_s3, 1);
  int verde = pulseIn(_out, LOW);
  return verde;
}
int lecturaAzul(byte _s2, byte  _s3, byte  _out) {
  digitalWrite(_s2, 0);
  digitalWrite(_s3, 1);
  int azul = pulseIn(_out, LOW);
  return azul;
}


