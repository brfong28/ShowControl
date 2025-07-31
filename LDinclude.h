/******************************************************************************/
// File: LDinclude.h
// Project: ShowControl2
// Description: LD (LCD driver) include file
// Author: Bruce Fong
// Date: 2025-07-11
/******************************************************************************/
#if !defined(LDversion) // To ensure the header is included only once
#define LDversion 0.0
/******************************************************************************/
// Globals
/******************************************************************************/
/*===============*/
// Global Defines
/*===============*/
#define LDROWS 4		// Rows in display
#define LDCOLS 20		// Columns in Display
#define LDBASEADD 0x27	// I2C LCD base Address
#define LDDISPLAYMAX 1	// Maximum Number of LCD displays
/*===============-=*/
// Global Includes
/*================*/
#include <LiquidCrystal_I2C.h>

/*============================================================================*/
/******************************************************************************/
// Class Definition
/******************************************************************************/
class LDDISPLAY /* : public LiquidCrystal_I2C */ {
public:
	// Constructor
	LDDISPLAY(uint8_t i2cAdd, uint8_t cols, uint8_t rows);

	// Public methods
	void init();
	void backlight();
	void put(uint8_t col, uint8_t row, unsigned long number);
	void put(uint8_t col, uint8_t row, String str);
private:
	// Private members
	LiquidCrystal_I2C *display;
	// Private methods

};
/*****************************/
// Constructor Implementation
/*****************************/
/*================*/
// No Arguments - Set all private Variables to default values
/*================*/
LDDISPLAY::LDDISPLAY (uint8_t i2cAdd=LDBASEADD, uint8_t cols=LDCOLS, uint8_t rows=LDROWS) {
	// Constructor code here

	display = new LiquidCrystal_I2C(i2cAdd, cols, rows);
}
/********************************/
// Public Method Implementations
/********************************/
/*================*/
//
/*================*/
void LDDISPLAY::init() {
	// Initialization code here
	display->init();
}
/*================*/
//
/*================*/
void LDDISPLAY::backlight() {
	// backlight code here
	display->backlight();
}
/*================*/
//
/*================*/
void LDDISPLAY::put(uint8_t col, uint8_t row, unsigned long num) {
	// display code here
	display->setCursor(col, row);
	display->print(num);
}
/*================*/
//
/*================*/
void LDDISPLAY::put(uint8_t col, uint8_t row, String str) {
	// display code here
	display->setCursor(col, row);
	display->print(str);
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
LDDISPLAY lcd1;	// LCD #1 at default address (0x27)
/******************************************************************************/
// 
/******************************************************************************/

/*======================*/
// Library Start routine
/*======================*/
bool LDstart() {
	// Start the LD (LCD Driver)

	lcd1.init();
	lcd1.backlight();
}
/******************************************************************************/
// End of Template Class
/******************************************************************************/
#endif // LDversion