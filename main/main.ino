#include <Arduino_LSM9DS1.h>

//Praeprozessoranweisungen
#define DISP_ACC       0 // wenn 1 Accelerometer wird als Ausgabe gezeigt 
#define DISP_MAG       0 // wenn 1 Magnetometer wird als Ausgabe gezeigt 
#define DISP_GYRO      0 // wenn 1 Gyroskop wird als Ausgabe gezeigt 
#define DISP_ALL       1 // wenn 1 Alle Sensoren wird als Ausgabe gezeigt 
#define BUFFER_LENGTH  512

//Variablen fuer Sensoren
float x,y,z;
float x2,y2,z2;
float x3,y3,z3;
char puffer[BUFFER_LENGTH];

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Board ist aktiv");
  
  if(!IMU.begin()){
    Serial.print("Fehler bei Initialisierung des Sensors");
    while(1);
    }
}

void loop() {
  if(IMU.accelerationAvailable()){
    IMU.readAcceleration(x,y,z);  
  }
  if(IMU.magneticFieldAvailable()){
    IMU.readMagneticField(x2,y2,z2);
  }
  if(IMU.gyroscopeAvailable()){
    IMU.readGyroscope(x3,y3,z3);
  }

#if DISP_ACC
  sprintf(puffer, "a_X:%4.3f\t | a_Y:%4.3f\t | a_Z:%4.3f\t",x,y,z);
#endif

#if DISP_MAG
  sprintf(puffer, "m_X:%4.3f\t | m_Y:%4.3f\t | m_Z:%4.3f\t",x2,y2,z2);
#endif

#if DISP_GYRO
  sprintf(puffer, "g_X:%4.3f\t | g_Y:%4.3f\t | g_Z:%4.3f\t",x3,y3,z3);
#endif

#if DISP_ALL
  sprintf(puffer, "a_X:%f a_Y:%f a_Z:%f m_X:%f m_Y:%f m_Z:%f g_X:%f g_Y:%f g_Z:%f",x,y,z,x2,y2,z2,x3,y3,z3);
#endif
  
  Serial.println(puffer);
  delay(100);
}
