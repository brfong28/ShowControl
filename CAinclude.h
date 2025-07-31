/******************************************************************************/
// File: CAinclude.h
// Project: ShowControl2
// Description: LD (Coin Acceptor HX-916 driver) include file
// Author: Bruce Fong
// Date: 2025-07-30
/******************************************************************************/
#if !defined(CAversion) // To ensure the header is included only once
#define CAversion 0.0
/******************************************************************************/
// Globals
/******************************************************************************/
/*===============*/
// Global Defines
/*===============*/
#define CA_PIN 2
#define CA_EEPROM_ADDRESS 0
/*===============-=*/
// Global Includes
/*================*/
#include <EEPROM.h>

/*============================================================================*/
/******************************************************************************/
// Class Definition
/******************************************************************************/
class CACLASS {
public:
	// Constructor
	CACLASS();

	// Public methods
	void interrupt();
	int getAccepted();
	int writeEEPROM();
	int readEEPROM();
	int set1Less();
	int set1More();
	bool isZero();
	bool isSaved();
private:
	// Private members
	int centsAccepted;
	bool saved;
	// Private methods

};
/*****************************/
// Constructor Implementation
/*****************************/
/*================*/
// No Arguments - Set all private Variables to default values
/*================*/
CACLASS::CACLASS () {
	// Constructor code here

}
/********************************/
// Public Method Implementations
/********************************/

/*================*/
//
/*================*/
int CACLASS::getAccepted() {
	// code here
	return centsAccepted;
}
/*================*/
//
/*================*/
int CACLASS::writeEEPROM() {
	// code here
	int current_value;
	EEPROM.get(CA_EEPROM_ADDRESS, current_value);
	if (current_value != centsAccepted) {
		EEPROM.put(CA_EEPROM_ADDRESS, centsAccepted);
		saved = true;
		return centsAccepted;
	}
	return -1;
}
/*================*/
//
/*================*/
int CACLASS::readEEPROM() {
	// code here
	EEPROM.get(CA_EEPROM_ADDRESS, centsAccepted);
	if (centsAccepted < 0) {
		centsAccepted = 0;
	//	writeEEPROM();
		return centsAccepted;
	}
	return -1;
}
/*================*/
//
/*================*/
int CACLASS::set1Less() {
	// code here
	if (centsAccepted > 0) {
		centsAccepted--;
		saved = false;
	}
	return centsAccepted;
}
/*================*/
//
/*================*/
int CACLASS::set1More() {
	// code here
	centsAccepted++;
	saved = false;
	return centsAccepted;
}
/*================*/
//
/*================*/
bool CACLASS::isZero() {
	// code here
	if (centsAccepted == 0) return true;
	return false;
}
/*================*/
//
/*================*/
bool CACLASS::isSaved() {
	// code here
	return saved;
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
CACLASS coinsAccepted;	// 
/******************************************************************************/
// 
/******************************************************************************/
/*================*/
//
/*================*/
static void CAinterrupt() {
	// code here
	coinsAccepted.set1More();
}
/*======================*/
// Library Start routine
/*======================*/
bool CAstart() {
	// Start the CA (Coin Acceptor Driver)
#if defined(__DEBUG__)
	Serial.println("==> CAsetup called");
#endif
	SSstart();					// call Seven segment start

	pinMode(CA_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(CA_PIN), CAinterrupt, FALLING);

	coinsAccepted.readEEPROM();

#if defined(__DEBUG__)
	Serial.println("<== CAsetup return");
#endif
	
}
/******************************************************************************/
// End of Template Class
/******************************************************************************/
#endif // CAversion