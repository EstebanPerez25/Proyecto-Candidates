#ifndef SensorColor_h
#define SensorColor_h

class sensorColor {

  private:

    byte _s2;
    byte _s3;
    byte _out;
    int colores[8][3];
  public:
    //Constructor
    int coloresI[8][3] = {

      {33,35,12},
      {36,54,18},
      {96,165,45},
      {90,55,20},
      {77,75,30},
      {50,144,28},
      {143,147,50},
      {22,59,13},

    };

    int coloresD[8][3] = {
      {38,45,14},
      {44,69,22},
      {114,213,55},
      {108,71,24},
      {87,92,34},
      {57,183,33},
      {175,189,58},
      {27,78,16},
      };

    /*Copiar y rellenar*
      {
      {,,},
      {,,},
      {,,},
      {,,},
      {,,},
      {,,},
      {,,},
      {,,},
      };
    */

    //Matriz que almacena los valores r g b de cada color Formato ---->  { {asda},{asd} };
    int colorRegistrado;           //Almacena el nÃºmero del color que fue identificado mÃ¡s veces
    sensorColor(byte s2, byte s3, byte out, bool n);

    //MÃ©todos
    int valoresRGB();                 //Encuentra los valores rgb para cada color, luego agregar estos valores a la matriz
    void imprimeMatriz();

    //Getters
    int getColor();                   //Lee el color que detecta el sensor
};


#endif

