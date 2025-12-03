/******************************************************************************/
// File: SSinclude.h
// Project: ShowControl
// Description: SS (Seven-segment TM1637) display driver
// Author: Bruce Fong
// Date: 2025-07-30
/******************************************************************************/
#if !defined(SSversion) // To ensure the header is included only once
#define SSversion 0.0
/******************************************************************************/
// Globals
/******************************************************************************/
/*===============*/
// Global Defines
/*===============*/

#define SS_DIO_PIN 3
#define SS_CLK_PIN 4
/*===============-=*/
// Global Includes
/*================*/
#include <TM1637Display.h>

/*============================================================================*/
/******************************************************************************/
// Class Definition
/******************************************************************************/
class SSCLASS {
public:
	// Constructor
	SSCLASS();

	// Public methods
	void showNumber(int number);
	void clear();
	void setBrightness(uint8_t);
private:
	// Private members
	TM1637Display* driver;
	// Private methods
};
/*****************************/
// Constructor Implementation
/*****************************/
/*================*/
// No Arguments - Set all private Variables to default values
/*================*/
SSCLASS::SSCLASS() {
		// Constructor code here
		driver = new TM1637Display(SS_CLK_PIN, SS_DIO_PIN);   // 7 Segment display #1
}
/********************************/
// Public Method Implementations
/********************************/

/*================*/
//
/*================*/
//*****************************************************************************************************
// showNumber - show number on Seven Segment
//*****************************************************************************************************
void SSCLASS::showNumber(int number) {
	driver->showNumberDec(number, false, 4, 0);
}
/*================*/
//
/*================*/
//*****************************************************************************************************
// clear - clear 
//*****************************************************************************************************
void SSCLASS::clear() {
	driver->clear();;
}
/*================*/
//
/*================*/
//*****************************************************************************************************
// setBrightness - set brightness
//*****************************************************************************************************
void SSCLASS::setBrightness(uint8_t number) {
	driver->showNumberDec(number, false, 4, 0);
}
/*********************************/
// Private Method Implementations
/*********************************/
/******************************************************************************/
// End of Class Definition
/**************** **************************************************************/
/******************************************************************************/
// Implementarion Variables
/******************************************************************************/
SSCLASS sevenseg1;   // 7 Segment display #1
/******************************************************************************/
// 
/******************************************************************************/
/*======================*/
// Library setup routine
/*======================*/
bool SSsetup() {
	// Start the SS (Seven Segmqnt display) driver
#if defined(__DEBUG__)
	Serial.println("==> SSsetup called");
#endif

	sevenseg1.clear();
	sevenseg1.setBrightness(0x0a);  // set display to maximum brightness
	sevenseg1.showNumber(8888);
	delay(1000);
	sevenseg1.clear();

#if defined(__DEBUG__)
	Serial.println("<== SSsetup return");
#endif
	
}
/******************************************************************************/
// End of Template Class
/******************************************************************************/
#endif // SSversion