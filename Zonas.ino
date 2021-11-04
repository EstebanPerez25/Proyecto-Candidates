#include "Zonas.h"
#include "Navegacion.h"
#include "SensorColor.h"
#include "SensorUltrasonico.h"


float distancia;             //Variable para distancia detectada por ultrasÃ³nicos
byte ds = 15;               // Distancia para considerar pared al frente


//3 Sensores UltrasÃ³nicos. (1 seÃ±al de Trig para los 3)
#define trign 3
#define echo_I   A0
#define echo_F   A1
#define echo_D   A2
//2 Sensores de color. (s0 y s1 estÃ¡n conectados a Vcc; s2 y s3 alimenta esos pines de ambos sensores)
#define s2n 4
#define s3n 5
#define out_I A3
#define out_D A4
//Controlador Motorreductores
#define in1n 6
#define in2n 7
#define in3n 8
#define in4n 9
//Servomotor
#define servoM 10
//Led RGB       AquÃ­ llamaremos a la funiÃ³n para endender el led, usando el dato recibido de la funciÃ³n getColor, o de la Zona C
#define led_Rn  11
#define led_Gn  12
#define led_Bn  13
//Para el Sensor AcelerÃ³metro/Giroscopio de usan lo pines 2, SCL y SDA de Arduino

/////////////////////////////////////////////////////////////////OBJETOS o INSTANCIAS
//Sensores UltrasÃ³nicos
sensorUltrasonico sensorUS_I(trign, echo_I);
sensorUltrasonico sensorUS_F(trign, echo_F);
sensorUltrasonico sensorUS_D(trign, echo_D);
//Sensores de Color
sensorColor sensorC_I(s2n, s3n, out_I, 0);
sensorColor sensorC_D(s2n, s3n, out_D, 1);
////Sensor AcelerÃ³metro y Giroscopio
//sensorAyG orientacionAyG;
//NavegaciÃ³n del Robot
navegacion navegar(in1n, in2n, in3n, in4n);
//Para .accion : 0-> Apagar motores 1-> Giro a la izquierda. 2-> Giro a la derecha. 3-> Giro 180 4-> Avanzar
//LedRGB
//AquÃ­ llamaremos a la funiÃ³n para endender el led, usando el dato recibido de la funciÃ³n getColor, o de la Zona C
ledRGB led_rgb(led_Rn, led_Gn, led_Bn);


//TEST
//sensorC_I.valoresRGB(); sensorC_I.imprimeMatriz(); do {} while (true);     //Obtiene valores r g b para agregar a la matriz de getColor  (Usar 1 vez al inicio)
//int colorActual = sensorC_I.getColor(); Serial.println(colorActual); // Obtiene el color actual del suelo
//orientacionAyG.offsetsM();                                                    //Obtener offsets del sensor y luego remplazarlos
//distancia= sensorUS_I.distancia(); for (int n = 0; n<10;n++){Serial.println(distancia);delay(1000);}

//    navegar.accion(1);
//    Serial.println("90 a la Izquierda");
//    delay(2000);
//
//    navegar.accion(2);
//    Serial.println("90 a la Derecha");
//    delay(2000);


//Test movimientos
//    navegar.accion(1);
//    Serial.println("okay");
//    navegar.accion(2);
//    Serial.println("okay2");
//    navegar.accion(2);
//    Serial.println("okay3");
//    navegar.accion(3);
//    Serial.println("okay4");

//Constructor

zonas::zonas() {

}


/////////////////////////////////////////////////////////////////////////////////////////////////////// METODOS
void zonas::test() {
  Serial.println(sensorC_I.getColor());
    Serial.println(sensorC_D.getColor());
    Serial.println("OK1");
    delay(3000);
    Serial.println(sensorC_I.getColor());
    Serial.println(sensorC_D.getColor());
    Serial.println("OK2");
    delay(3000);
    Serial.println(sensorC_I.getColor());
    Serial.println(sensorC_D.getColor());
    Serial.println("OK3");


  //  while (sensorUS_F.distancia() > 25) {
  //    navegar.accion(4);
  //    Serial.println(sensorUS_F.distancia());
  //  }
  //  navegar.accion(0);
  
//  while (true) {
//    Serial.println(sensorUS_I.distancia());
//    Serial.println(sensorUS_F.distancia());
//    Serial.println(sensorUS_D.distancia());
//    Serial.println("*-------------------------*");
//    delay(200);
//  }

}

void zonas::calibrar() {
  //Los datos recopilados deben remplazarse en sus respectivas clases
  sensorC_I.valoresRGB(); Serial.println("*------------------------------------------------------------*"); //Obtener valores RGB para cada color
  sensorC_D.valoresRGB();
  //  Serial.println("Pon el robot en la posiciÃ³n para calibrar, tienes 5 egundos..."); delay(5000);
  //  orientacionAyG.offsetsM();                         //Obtener offsets a remplazar de AcelerÃ³metro y Giroscopio
}

/////////////////////////////////////////////////////////////////////////////////////////// ZONA A
void zonas::zonaA() {
  byte v = 350;
  while (true) {
    if ((sensorUS_F.distancia() > 25.0) && (sensorUS_I.distancia() > 30.0)) {//Toda libre
      delay(250);
      navegar.accion(0);
      navegar.accion(1);
      navegar.accion(4);
      delay(v);
      navegar.accion(0);
    }
    else if ((sensorUS_F.distancia() > 25.0) && (sensorUS_I.distancia() < 30.0)) { //Frente libre
      navegar.accion(4);
      delay(v);
      navegar.accion(0);

    }
    else if ((sensorUS_F.distancia() < 25) && (sensorUS_I.distancia() > 30))  {//Izquierda libre
      delay(250);
      navegar.accion(1);
      delay(v);
      navegar.accion(0);
      navegar.accion(4);
    }
    else {// Ninguna
      navegar.accion(2);

    }

  }
}


/////////////////////////////////////////////////////////////////////////////////////////// ZONA B
void zonas::zonaB() {

  for (int n = 0; n < 6; n++) {
    while (sensorUS_F.distancia() > 25) {
      navegar.accion(1);
    }
    navegar.accion(0);
    navegar.accion(1);
  }//Llega hasta esquina inferior derecha
  while (sensorUS_D.distancia() < 30) {
    navegar.accion(4);
  }
  delay(350);
  navegar.accion(0);
  navegar.accion(2);
  navegar.accion(4);
  delay(450);
  navegar.accion(0);

}



/////////////////////////////////////////////////////////////////////////////////////////// ZONA C
void zonas::zonaC() {
  byte left = 0;
  byte right = 0;
  byte sum = 0;
  byte binary_sum = 0;

  byte cI; //Color Inicial Izquierda
  byte cD; //Color Inicial Izquierda
  Serial.println("PreparaciÃ³n");

  do {
    cI = sensorC_I.getColor();
    cD = sensorC_D.getColor();
    navegar.accion(4); //Avanza hasta detectar color
    Serial.println("Avanza");
    if ((sensorUS_F.distancia() < 15) || (sensorC_I.getColor() != cI) || (sensorC_D.getColor() != cD) ) {
      Serial.println(sensorUS_F.distancia());
      Serial.println(sensorC_D.getColor());
      Serial.println(sensorC_I.getColor());
      navegar.accion(0);
      Serial.println("Alto");

      //Hacer sumas de color
      if (sensorC_I.getColor() == 1) { // yellow
        left += 1;
      } else if (sensorC_I.getColor() == 4) { // green
        left += 2;
      } else if (sensorC_I.getColor() == 6) { // black
        right = 0;
      } else if (sensorC_I.getColor() == 0) { // white
        left += 0;
      }

      if (sensorC_I.getColor() == 1) { // yellow
        right += 1;
      } else if (sensorC_I.getColor() == 4) { // green
        right += 2;
      } else if (sensorC_I.getColor() == 6) { // black
        left = 0;
      } else if (sensorC_I.getColor() == 0) { // white
        right += 0;

        sum = (left + right);
        binary_sum = dec_to_bin(sum);

        if ((sensorUS_F.distancia() < ds) && (binary_sum % 2 == 0)) { // pair
          navegar.accion(1); //Giro Izquierda
        } else if ((sensorUS_F.distancia()) < ds && (binary_sum % 2 != 0)) { // odd
          navegar.accion(2); //Giro Derecha
        }
      }
    }//End if sumatorias
  } while (sensorC_I.getColor() != 7);//Hace el algoritmo de la zona mientras no llegue al check point de la rampa color ROSA

}//End Zona C


void zonas::rampa() {
  navegar.accion(2); //Giro Izquierda
  while ((sensorUS_F.distancia() < ds)) {
    navegar.accion(5); //Avanzar
  }
}


//////////Funciones extra zona C
int dec_to_bin(int dec) {
  int bin[8];
  int lenght = sizeof(bin);

  for (int i = 0; i < 8; i++) {
    bin[i] = dec % 2;
    dec = dec / 2;
  }

  for (int i = 7; i >= 0; i--) {
    if (bin[i] == 0) {
      led_rgb.rojo();
    } else if (bin[i] == 1) {
      led_rgb.verde();
    }
  }

  led_rgb.azul(); //Encendido led azul para indicar fin de secuencia binario
  return bin[last_element(bin, lenght)];
}

// Get Last Element
int last_element(int aray[], int lenght) {
  int last = 0;
  last = (lenght / sizeof(aray[0]) - 8 );
  return last;
}

