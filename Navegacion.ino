#include "Navegacion.h"

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 mpu;
#define OUTPUT_READABLE_YAWPITCHROLL

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n' };



// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
  mpuInterrupt = true;
}



// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================


//////////////////////////////////////////////////////////////

bool s;
int ang;
int vA;
int izq;
int dcha;
int g180;

/////////////////////////////////////////////////////////////////////////CONSTRUCTOR
navegacion::navegacion(byte in1, byte in2, byte in3, byte in4) {
  _in1 = in1;
  _in2 = in2;
  _in3 = in3;
  _in4 = in4;

  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
  pinMode(_in3, OUTPUT);
  pinMode(_in4, OUTPUT);


}

/////////////////////////////////////////////////////////////////////////////MÃ‰TODOS
//g Variable para hacer una acciÃ³n : 0-> Apagar motores 1-> Giro a la izquierda. 2-> Giro a la derecha. 3-> Giro 180 4-> Avanzar
void navegacion::accion(byte g) {
  
lecturaAyG(g,_in1,_in2,_in3,_in4);
  /*byte f = 250;
  switch (g) {
    case 0:
      digitalWrite(_in1, 0);
      digitalWrite(_in2, 0);
      digitalWrite(_in3, 0);
      digitalWrite(_in4, 0);
      break;

    case 1:
      digitalWrite(_in2, 1);
      digitalWrite(_in3, 1);
      delay(f);
      digitalWrite(_in2, 0);
      digitalWrite(_in3, 0);
      break;


    case 2:
      digitalWrite(_in1, 1);
      digitalWrite(_in4, 1);
      delay(f);
      digitalWrite(_in1, 0);
      digitalWrite(_in4, 0);
      break;


    case 3:
      digitalWrite(_in1, 1);
      digitalWrite(_in4, 1);
      delay(2 * f);
      digitalWrite(_in1, 0);
      digitalWrite(_in4, 0);
      break;

    case 4:
      digitalWrite(_in1, 1);
      digitalWrite(_in3, 1);
      break;

    case 5:
      digitalWrite(_in2, 1);
      digitalWrite(_in4, 1);
      break;
  }*/
}



///////////////////////////////////////////////////////////Funciones para funcionamiento de AcelerÃ³metro y Giroscopio

int lecturaAyG(byte g, byte _in1, byte _in2, byte _in3, byte _in4) {
  //Serial.println("Test2 OK");

  ///////////////////////////////////////////////

  if (s == 0) {       //Void setup


    // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
#endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    // NOTE: 8MHz or slower host processors, like the Teensy @ 3.3v or Ardunio
    // Pro Mini running at 3.3v, cannot handle this baud rate reliably due to
    // the baud timing being too misaligned with processor ticks. You must use
    // 38400 or slower in these cases, or use some kind of external separate
    // crystal solution for the UART timer.

    // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    //     wait for ready
    //      Serial.println(F("\nSend any character to begin DMP programming and demo: "));
    //      while (Serial.available() && Serial.read()); // empty buffer
    //      while (!Serial.available());                 // wait for data
    //      while (Serial.available() && Serial.read()); // empty buffer again


    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    ///////////////////////////////////////////////////////////////////////////////////////////////////// AQUÃ� CAMBIA LOS OFFSETS
    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(63 );
    mpu.setYGyroOffset(-45);
    mpu.setZGyroOffset(-5);
    mpu.setZAccelOffset(4665); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
      // turn on the DMP, now that it's ready
      Serial.println(F("Enabling DMP..."));
      mpu.setDMPEnabled(true);

      // enable Arduino interrupt detection
      Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
      attachInterrupt(0, dmpDataReady, RISING);
      mpuIntStatus = mpu.getIntStatus();

      // set our DMP Ready flag so the main loop() function knows it's okay to use it
      Serial.println(F("DMP ready! Waiting for first interrupt..."));
      dmpReady = true;

      // get expected DMP packet size for later comparison
      packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      Serial.print(F("DMP Initialization failed (code "));
      Serial.print(devStatus);
      Serial.println(F(")"));
    }
    s = 1;
  }
  int t = 0;
  int d = 0;
  //mpu.initialize();
  while (true) {

    // ================================================================
    // ===                    MAIN PROGRAM LOOP                     ===
    // ================================================================


    // if programming failed, don't try to do anything

    if (!dmpReady) {
      Serial.print("FAILED");
      return;
    }

    // wait for MPU interrupt or extra packet(s) available
    //    while (!mpuInterrupt && fifoCount < packetSize) {
    //      // other program behavior stuff here
    //      // .
    //      // .
    //      // .
    //      // if you are really paranoid you can frequently test in between other
    //      // stuff to see if mpuInterrupt is true, and if so, "break;" from the
    //      // while() loop to immediately process the MPU data
    //      // .
    //      // .
    //      // .
    //    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
      // reset so we can continue cleanly
      mpu.resetFIFO();
      Serial.println(F("FIFO overflow!"));

      // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
      // wait for correct available data length, should be a VERY short wait
      while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

      // read a packet from FIFO
      mpu.getFIFOBytes(fifoBuffer, packetSize);

      // track FIFO count here in case there is > 1 packet available
      // (this lets us immediately read more without waiting for an interrupt)
      fifoCount -= packetSize;

#ifdef OUTPUT_READABLE_YAWPITCHROLL
      // display Euler angles in degrees
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      //Serial.print("ypr\t");
      /*Serial.print(ypr[0] * 180 / M_PI);*/ ang = (ypr[0] * 180 / M_PI) - vA; // <<< <<< <<< <<< <<< <<< Valor a Recuperar
      //      Serial.print("\t");
      //      Serial.print(ypr[1] * 180 / M_PI);
      //      Serial.print("\t");
      //      Serial.println(ypr[2] * 180 / M_PI);
#endif

    }

    /////////////////////////////////////////////

    if (t == 0) {
      Serial.println("Tiempo de espera");

      if (d == 1000) {
        vA = ang;
        Serial.print("vA: "); Serial.println(vA);
        izq = 90;
        Serial.print("I: "); Serial.println(izq);
        dcha =  - 90;
        Serial.print("D: "); Serial.println(dcha);
        g180 = 178;
        Serial.print("G: "); Serial.println(g180);

        //        if (g180 < -179 || g180 > 179) {
        //          g180 -= (180 - 85) ;
        //        }
        t = 1;
        //d = 0;
      } else {
        d += 1;
        Serial.println(d);
      }
    }

    if (t == 1) {
      switch (g) {
        case 0:
          digitalWrite(_in1, LOW);
          digitalWrite(_in2, LOW);
          digitalWrite(_in3, LOW);
          digitalWrite(_in4, LOW);
          s = 0;
          return;
          break;


        case 1:
          if ( ang < izq) {
            digitalWrite(_in1, HIGH);
            digitalWrite(_in4, HIGH);
            Serial.println(ang);
            Serial.print(" i  "); Serial.println(izq);
          }
          else {
            digitalWrite(_in1, LOW);
            digitalWrite(_in4, LOW);
            s = 0;
            return;
          }

          break;

        case 2:
          if (ang > dcha) {
            digitalWrite(_in2, HIGH);
            digitalWrite(_in3, HIGH);
            Serial.println(ang);
            Serial.print("  d "); Serial.println(dcha);
          }
          else {
            digitalWrite(_in2, LOW);
            digitalWrite(_in3, LOW);
            s = 0;
            return;
          }
          break;

        case 3:
          if (ang < g180) {
            digitalWrite(_in1, HIGH);
            digitalWrite(_in4, HIGH);
            Serial.println(ang);
            Serial.print(" r "); Serial.println(g180);
          }
          else {
            digitalWrite(_in1, LOW);
            digitalWrite(_in4, LOW);
            s = 0;
            return;
          }
          break;

        case 4:
          //          digitalWrite(_in1, HIGH);
          //          digitalWrite(_in3, HIGH);

          if (ang < (vA + 2) && ang > (vA - 2)) {
            digitalWrite(_in1, HIGH);
            digitalWrite(_in3, HIGH);
            Serial.print("ok   ");Serial.println(ang);
          }
          
          else if (ang > (vA + 1)) {
            digitalWrite(_in3, LOW);
            delay(100);
            Serial.print("izq   ");Serial.println(ang);
            digitalWrite(_in3, HIGH);
          }
          
          
          else if (ang < (vA - 1)) {
            digitalWrite(_in1, LOW);
            Serial.print("dcha   ");Serial.println(ang);
            delay(100);
            digitalWrite(_in1, HIGH);
          }
          
          s = 0;
          break;

          //return;
      }
    }
  }
}


