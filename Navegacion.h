#ifndef Navegacion_h
#define Navegacion_h

class navegacion {
  private:
    byte _in1;
    byte _in2;
    byte _in3;
    byte _in4;

  public:
    //Constructor
    navegacion (byte in1, byte in2, byte in3, byte in4);

    //MÃ©todos
    void accion(byte g);                    //g: 1-> Giro a la izquierda. 2-> Giro a la derecha. 3-> Giro 180
    
};


#endif

