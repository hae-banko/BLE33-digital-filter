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
float dt = 0.01; // dt: 0.01; Frequenz der Sensoren sind 500, d.h. dt = 0.002
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
	
	// Drift-Korrektur von Gyroskop
	hf1 = calData.G.x - 2.01; // 2.01 war manuell bestimmt
	hf2 = calData.G.y + 0.67; // 0.67 war manuell bestimmt

	// Integrierer
	roll_g  += (hf1 * dt);
	pitch_g -= (hf2 * dt);

	// Winkelberechnung aus Accelerometer
	roll_a  = atan2f( sqrt((calData.A.x * calData.A.x) + (calData.A.z * calData.A.z)), calData.A.y) * angles_divided_by_pi; // Bereich: 180 grad
	pitch_a = atan2f( sqrt((calData.A.y * calData.A.y) + (calData.A.z * calData.A.z)), calData.A.x) * angles_divided_by_pi; // Bereich: 180 grad
	
	// Complementary Filter
	roll_g  = (0.98) * (roll_g)   + (0.02 * roll_a);
	pitch_g = (0.98) * (pitch_g)  + (0.02 * pitch_a);
	
	// Konsoleausgabe
	Serial.print("Roll: ");
	Serial.print(roll_g);
	Serial.print("\t");
	Serial.print("Pitch: ");
	Serial.println(pitch_g); // Automatisch '\n' am Ende hinzufuegen
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

// Schleife
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
