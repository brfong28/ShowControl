/******************************************************************************/
// File: PBinclude.h
// Project: ShowControl
// Description: PB (Push Button LED) driver
// Author: Bruce Fong
// Date: 2025-08-10
/******************************************************************************/
#if !defined(PBversion) // To ensure the header is included only once
#define PBversion 0.0
/******************************************************************************/
// Globals
/******************************************************************************/
/*===============*/
// Global Defines
/*===============*/
// #define PBPIN 10   // PBMRRC Used - Not an Interrupt pin
#define PBPIN 19      // MEGA use - Pin with interrups

#define PBDEBOUNCE 750
/*===============-=*/
// Global Includes
/*================*/
#include <LSinclude.h>

/*============================================================================*/
/******************************************************************************/
// Class Definition
/******************************************************************************/
class PBCLASS {
public:
	// Constructor
	PBCLASS();

	// Public methods
	bool pushEvent();
	bool isPushed();
	bool isPushed(bool reset);

private:
	// Private members
	bool pushed;
	unsigned long pushTime;
	uint8_t pin;
	// Private methods

};
/*****************************/
// Constructor Implementation
/*****************************/
/*================*/
// No Arguments - Set all private Variables to default values
/*================*/
PBCLASS::PBCLASS() {
	// Constructor code here
	pushed = false;
	pin = PBPIN;
	pushTime = 0;
}
/********************************/
// Public Method Implementations
/********************************/
/*================*/
//
/*================*/
bool PBCLASS::pushEvent() {
	if ((millis() - pushTime) >= PBDEBOUNCE) {
#if defined(__DEBUG__)
		Serial.println("*** PB Pushed");
#endif
		// LEDSset(0, 0, 0, 255, 0);   // GREEN
		pushed = true;
		pushTime = millis();
	};
};
/*================*/
//
/*================*/
bool PBCLASS::isPushed() {
	return pushed;
}
bool PBCLASS::isPushed(bool reset) {
	bool current = pushed;
	if (reset) pushed = false;
	return current;
}
/*********************************/
// Private Method Implementations
/*********************************/
/******************************************************************************/
// End of Class Definition
/******************************************************************************/
/******************************************************************************/
// Implementarion Variables
/******************************************************************************/
PBCLASS pb1;
/******************************************************************************/
// 
/******************************************************************************/
/*================*/
//
/*================*/
static void PBinterrupt() {
	// code here
	pb1.pushEvent();
};
//*****************************************************************************************************
// 
//*****************************************************************************************************
/*======================*/
// Library setup routine
/*======================*/
bool PBsetup() {
	// Start the PB (Push Button) driver
#if defined(__DEBUG__)
	Serial.println("==> SSsetup called");
#endif

	pinMode(PBPIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(PBPIN), PBinterrupt, RISING);

#if defined(__DEBUG__)
	Serial.println("<== SSsetup return");
#endif
	
}
/******************************************************************************/
// End of Template Class
/******************************************************************************/
#endif // PBversion