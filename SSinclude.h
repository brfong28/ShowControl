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
#include <TM1637Display.h>

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
/*********************************/
// Private Method Implementations
/*********************************/
/******************************************************************************/
// End of Class Definition
/******************************************************************************/
/******************************************************************************/
// Implementarion Variables
/******************************************************************************/
TM1637Display sevenseg1(SS_CLK_PIN, SS_DIO_PIN);   // 7 Segment display #1
/******************************************************************************/
// 
/******************************************************************************/
//*****************************************************************************************************
// SEVENSEGdisplay - Display number onSeven Segment
//*****************************************************************************************************
void SSdisplay(uint8_t display, int number) {
	sevenseg1.showNumberDec(number, false, 4, 0);
}
/*======================*/
// Library Start routine
/*======================*/
bool SSstart() {
	// Start the SS (Seven Segmqnt display) driver
#if defined(__DEBUG__)
	Serial.println("==> SSsetup called");
#endif

	sevenseg1.clear();
	sevenseg1.setBrightness(0x0a);  // set display to maximum brightness
	sevenseg1.showNumberDec(8888, true, 4, 0);
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