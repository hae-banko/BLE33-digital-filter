#include <Arduino_LSM9DS1.h>

//Variablen fuer Accelerometer
float x,y,z;
float x2,y2,z2;
float x3,y3,z3;
char puffer[512];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Board ist aktiv");
  
  if(!IMU.begin()){
    Serial.print("Fehler bei Initialisierung des Sensors");
    while(1);
    }
}

void dispAcc() {
    sprintf(puffer, "a_X:%4.3f\t | a_Y:%4.3f\t | a_Z:%4.3f\t",x,y,z);
  }
void dispMagn() {
    sprintf(puffer, "m_X:%4.3f\t | m_Y:%4.3f\t | m_Z:%4.3f\t",x2,y2,z2);
  }
void dispGyro() {
    sprintf(puffer, "g_X:%4.3f\t | g_Y:%4.3f\t | g_Z:%4.3f\t",x3,y3,z3);
  }
void dispAll() {
    sprintf(puffer, "a_X:%f a_Y:%f a_Z:%f m_X:%f m_Y:%f m_Z:%f g_X:%f g_Y:%f g_Z:%f",x,y,z,x2,y2,z2,x3,y3,z3);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(IMU.accelerationAvailable()){
    IMU.readAcceleration(x,y,z);  
  }
  if(IMU.magneticFieldAvailable()){
    IMU.readMagneticField(x2,y2,z2);
  }
  if(IMU.gyroscopeAvailable()){
    IMU.readGyroscope(x3,y3,z3);
  }

  //dispAcc();
  //dispMagn();
  //dispGyro();
  dispAll();
  
  Serial.println(puffer);
  delay(100);
}
