#ifndef LedRgb_h
#define LedRgb_h

class ledRGB {

  private:

    byte _ledR;
    byte _ledG;
    byte _ledB;

  public:
    //Constructor
    ledRGB( byte led_R, byte led_G, byte led_B) {

      _ledR = led_R;
      _ledG = led_G;
      _ledB = led_B;

      pinMode(_ledR, OUTPUT);
      pinMode(_ledG, OUTPUT);
      pinMode(_ledB, OUTPUT);

      //El led es positivo comÃºn, por lo que se debe aplicar lÃ³gica inversa para encender cada led (HIGH para apagarlo y LOW para encenderlo)
      //AquÃ­ apago todos los leds
      digitalWrite(_ledR, HIGH); digitalWrite(_ledG, HIGH); digitalWrite(_ledB, HIGH);
    }

    //MÃ©todos

    void rojo() {
      digitalWrite(_ledR, LOW); 
      digitalWrite(_ledG, HIGH); 
      digitalWrite(_ledB, HIGH);
      delay(1000);
      digitalWrite(_ledR, HIGH); 
    }
     void verde() {
      digitalWrite(_ledR, HIGH); 
      digitalWrite(_ledG, LOW); 
      digitalWrite(_ledB, HIGH);
      delay(1000);
      digitalWrite(_ledG, HIGH); 
    }
    
    void azul() {
      digitalWrite(_ledR, HIGH); 
      digitalWrite(_ledG, HIGH); 
      digitalWrite(_ledB, LOW);
      delay(1000);
      digitalWrite(_ledB, HIGH); 
    }
};

#endif

