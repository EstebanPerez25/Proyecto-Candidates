#ifndef SensorUltrasonico_h
#define SensorUltrasonico_h

class sensorUltrasonico {

  private:
    byte _trig;
    byte _echo;
    long _duracion;

  public:
    //Constructores
    float dist;                            //Esta variable corresponde a la distancia registrada por el sensor
    sensorUltrasonico(byte trig, byte echo);

    //MÃ©todos
    float distancia();

};

#endif

