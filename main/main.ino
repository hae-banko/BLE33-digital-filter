#include <Arduino_LSM9DS1.h>
#include <math.h>

//Praeprozessoranweisungen
#define DISP_ACC       0 // wenn 1 Accelerometer wird als Ausgabe gezeigt 
#define DISP_MAG       0 // wenn 1 Magnetometer wird als Ausgabe gezeigt 
#define DISP_GYRO      0 // wenn 1 Gyroskop wird als Ausgabe gezeigt 
#define DISP_ALL       0 // wenn 1 Alle Sensoren wird als Ausgabe gezeigt 
#define DISP_RYP       1 // wenn 1 Rollen, Nicken, Gieren werden gezeigt
#define ANGLE_HALF_PI  0 // wenn 1 Winkel wird zwischen 90 bis -90 Grad gezeigt
#define ANGLE_FULL_PI  1 // wenn 1 Winkel wird zwischen 0 bis 180 Grad gezeigt
#define BUFFER_LENGTH  512

//Variablen fuer Sensoren
float x,y,z;
float x2,y2,z2;
float x3,y3,z3;
float roll, pitch, yaw;
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

#if ANGLE_HALF_PI
  roll  = (y,atan2(y, sqrt((x * x) + (z * z)))) * 180/M_PI;
  pitch = (x,atan2(x, sqrt((y * y) + (z * z)))) * 180/M_PI;
  yaw   = (atan2(-y2, x2)) * 180/PI;
#endif

#if ANGLE_FULL_PI
  roll  = (atan2(sqrt((x * x) + (z * z)),y)) * 180/M_PI;
  pitch = (atan2(sqrt((y * y) + (z * z)),x)) * 180/M_PI;
  yaw   = (atan2(-y2, x2)) * 180/PI;
#endif

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
  sprintf(puffer, "a_X:%f a_Y:%f a_Z:%f m_X:%f m_Y:%f m_Z:%f g_X:%f g_Y:%f g_Z:%f roll:%f pitch:%f yaw:%f",x,y,z,x2,y2,z2,x3,y3,z3,roll,pitch,yaw);
#endif

#if DISP_RYP
  sprintf(puffer, "roll:%f pitch:%f yaw:%f", roll, pitch, yaw);
#endif
  

  Serial.println(puffer);
  delay(100);
}
