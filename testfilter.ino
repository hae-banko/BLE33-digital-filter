#include "Arduino.h"
#include "StateMachine.h"
#include "LoopCheck.h"
#include "testfilter.h"
#include "nRF52840Twi.h"
#include "SensorLSM9DS1.h"
#include "math.h"				// Atan2() Funktion

float roll, yaw, pitch;
float roll_a, yaw_a, pitch_a;
float roll_g, yaw_g, pitch_g;

LoopCheck lc;		//Loopcheck
nRF52840Twi twi;	//I2C-Bus

#define smCycle 5
StateMachine sm(smInit,NULL, smCycle); //StateMachine

#define sensorCycle 500
SensorLSM9DS1 imu ((IntrfTw *) &twi, sensorCycle); //Sensor

// =================================================================
//
// Zustandsmachine
//
// =================================================================

void smPrepare(){
	if(sm.firstEnter()){
		Serial.println("smPrepare");
	}
	sm.enter(smIdle, 10000);
}

void smInit(){
	if(sm.firstEnter())
		Serial.println("smInit");
	sm.enter(smPrepare, 100);
}

RawDataAG  rawData;
CalValueAG calData;
CalValue   calData2;
float dt = 0.01; // Testvariable: 0.01; Frequenz der Sensoren sind 500, d.h. dt = 0.002
float angles_divided_by_pi = 180/M_PI; // Hilfsvariable fuer leichtere Berechnung

float hf1,hf2;

void smGetDataAG()
{
	if(sm.firstEnter()){
		Serial.println("smGetDataAG");
	}

	if(!imu.getValuesAG(&calData)){
		return;
	}

	hf1 = calData.G.x - 2.01; // 2.01 war manuell bestimmt
	hf2 = calData.G.y + 0.67; // 0.67 war manuell bestimmt

	// Gyroskop
	roll_g  += (hf1 * dt);
	pitch_g -= (hf2 * dt);

	// Accelerometer
	roll_a  = atan2f( sqrt((calData.A.x * calData.A.x) + (calData.A.z * calData.A.z)), calData.A.y) * angles_divided_by_pi; // Bereich: 180 grad
	pitch_a = atan2f( sqrt((calData.A.y * calData.A.y) + (calData.A.z * calData.A.z)), calData.A.x) * angles_divided_by_pi; // Bereich: 180 grad

	// Alternative Berechnung der Winkel mit Accelerometer 90 Grad
	/*
	roll  = (y,atan2(y, sqrt((calData.A.x * calData.A.x) + (calData.A.z * calData.A.z))) * 180/M_PI;
  	pitch = (x,atan2(x, sqrt((y * y) + (z * z)))) * 180/M_PI;
    yaw   = (atan2(-y2, x2)) * 180/PI;
	*/

	roll_g  = (0.98) * (roll_g)   + (0.02 * roll_a);
	pitch_g = (0.98) * (pitch_g)  + (0.02 * pitch_a);

	Serial.print("Roll: ");
	Serial.print(roll_g);
	Serial.print("\t");
	Serial.print("Pitch: ");
	Serial.println(pitch_g); // Automatisch '\n' am Ende hinzufuegen
}


void smGetGyroOnly(){
	if (!imu.getValuesAG(&calData)){
		return;
	}

	roll_g  = (calData.G.x);
	pitch_g = (calData.G.y);

	Serial.print("x: ");
	Serial.print(roll_g - 2.2 -0.12 +0.31);
	Serial.print("\t");
	Serial.print("y: ");
	Serial.print(pitch_g + 0.67);
	Serial.print("\t");
	Serial.print("z: ");
	Serial.println(calData.G.z + 0.06);
}

void smInitAG(){
	Serial.println("initAG");
	sm.enter(smGetDataAG, 100);
}

void smIdle(){
	Serial.println("idle");
	sm.enter(smInitAG,100);
}

// =================================================================
//
// Sub-function
//
// =================================================================

unsigned long N = 1;
float gx, gy, gz;
float bias_x, bias_y, bias_z;
float mean_bias_x, mean_bias_y, mean_bias_z; // Durchschnittliche Abw.


// Noch nicht fertig
void smCalibrateGyro(){
	mean_bias_x, mean_bias_y, mean_bias_z = 0.0;

	// Greift die Messwerte von Inertialsensoren
	if(!imu.getValuesAG(&calData)){
			return;
	}

	// 10 Sekunde wird benutzt, um die durchschnittliche
	// Abweichung zu untersuchen.
	// Problem: Standard-Bibliothek millis() verfügbar?

	// Messwerte sind nicht 0 und ideale Werte von 0 werden
	// durch die Subtraktion der Messwerte und Abweichung
	// von 0 gekriegt
	bias_x = 0 - calData.G.x;
	bias_y = 0 - calData.G.y;
	bias_z = 0 - calData.G.z;

	// Formel:
	//
	// Messwert(N) + Messwert(N-1) + ... + Messwert(1)
	// -----------------------------------------------
	//                     N
	//
	mean_bias_x = mean_bias_x + (bias_x / N);
	mean_bias_y = mean_bias_y + (bias_y / N);
	mean_bias_z = mean_bias_z + (bias_z / N);

	N++;	// Abtastzahl inkrementieren

}

// =================================================================
//
// Setup and Loop
//
// =================================================================


void setup()
{
	TwiParams twiPar;

	Serial.begin(115200);

	// Initialisierung von Bus parameter
	twiPar.inst = 0;
	twiPar.type = TwiMaster;
	twiPar.clkPort = 0;
	twiPar.clkPin = 15;
	twiPar.dataPort = 0;
	twiPar.dataPin = 14;
	twiPar.speed = Twi100k;
	twi.begin(&twiPar);

	imu.begin(FreqAG119, 12, MaxAcc4g, MaxGyro2000dps, FreqM_OFF, 0, MaxMag4G);
	imu.syncValuesAG();
}

// The loop function is called in an endless loop
void loop()
{
	lc.begin();

	if(lc.timerMilli(lcTimer0, smCycle, 0)){
		sm.run();
	}

	if(lc.timerMicro(lcTimer1, sensorCycle, 0))
		imu.run();
	lc.end();
}
