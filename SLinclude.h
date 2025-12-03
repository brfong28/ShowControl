/******************************************************************************/
// File: SLinclude.h
// Project: ShowControl
// Description: SL (Servo and LED driver - PCA9685) include file 
// Author: Bruce Fong
// Date: 2025-07-14
/******************************************************************************/
#if !defined(SLversion) // To ensure the header is included only once
#define SLversion 0.0
/******************************************************************************/
// Globals
/******************************************************************************/
/*===============*/
// Global Defines
/*===============*/
#if !defined(SLSERVOmax)
#define SLSERVOmax 16
#endif


// Must specify this before the include of "ServoEasing.hpp"
#define USE_PCA9685_SERVO_EXPANDER    // Activating this enables the use of the PCA9685 I2C expander chip/board.
//#define PCA9685_ACTUAL_CLOCK_FREQUENCY 26000000L // Change it, if your PCA9685 has another than the default 25 MHz internal clock.
//#define USE_SOFT_I2C_MASTER           // Saves 1756 bytes program memory and 218 bytes RAM compared with Arduino Wire
//#define USE_SERVO_LIB                 // If USE_PCA9685_SERVO_EXPANDER is defined, Activating this enables force additional using of regular servo library.
//#define USE_LEIGHTWEIGHT_SERVO_LIB    // Makes the servo pulse generating immune to other libraries blocking interrupts for a longer time like SoftwareSerial, Adafruit_NeoPixel and DmxSimple.
//#define PROVIDE_ONLY_LINEAR_MOVEMENT  // Activating this disables all but LINEAR movement. Saves up to 1540 bytes program memory.
//#define DISABLE_COMPLEX_FUNCTIONS     // Activating this disables the SINE, CIRCULAR, BACK, ELASTIC, BOUNCE and PRECISION easings. Saves up to 1850 bytes program memory.
//#define DISABLE_MICROS_AS_DEGREE_PARAMETER // Activating this disables microsecond values as (target angle) parameter. Saves 128 bytes program memory.
//#define DISABLE_MIN_AND_MAX_CONSTRAINTS    // Activating this disables constraints. Saves 4 bytes RAM per servo but strangely enough no program memory.
//#define DEBUG                         // Activating this enables generate lots of lovely debug output for this library.

//#define ENABLE_EASE_QUADRATIC
//#define ENABLE_EASE_CUBIC
//#define ENABLE_EASE_QUARTIC
#define ENABLE_EASE_SINE
//#define ENABLE_EASE_CIRCULAR
//#define ENABLE_EASE_BACK
//#define ENABLE_EASE_ELASTIC
//#define ENABLE_EASE_BOUNCE
//#define ENABLE_EASE_PRECISION
//#define ENABLE_EASE_USER

#if !defined(MAX_EASING_SERVOS)
#define MAX_EASING_SERVOS SLSERVOmax
#endif

/*===============-=*/
// Global Includes
/*================*/
#include <ServoEasing.hpp>

#define FIRST_PCA9685_EXPANDER_ADDRESS  PCA9685_DEFAULT_ADDRESS // 0x40
#define SECOND_PCA9685_EXPANDER_ADDRESS (PCA9685_DEFAULT_ADDRESS  + 0x01) // Bridged A5 on the board -> 0x41
#define MAX_pin 15		// max pin number (0-xx) on expander

#define MAX_LEDS 24
#define LED_0_PULSE_WIDTH 0
#define LED_180_PULSE_WIDTH 4000
#define LED_180_PULSE_WIDTH_LAST 2900
#define MIN_LED_VALUE 0
#define MAX_LED_VALUE 180

#define MAX_SERVOS 8
#define DEG_0_PULSE_WIDTH 
#define DEGREE_180_PULSE_WIDTH 4000
#define MIN_DEGREE_VALUE 0
#define MAX_DEGREE_VALUE 180


#define START_DEGREE_VALUE 0
#define START_LED_VALUE 0
/*============================================================================*/
/******************************************************************************/
// Class Definition
/******************************************************************************/
/*===================================================================*/
/* Class: SLDEVICE                                                   */
/*===================================================================*/
class SLDEVICE {
public:
	// Constructor
	SLDEVICE(uint8_t dev, uint8_t i2cAddr, uint8_t pin, bool led);
	// Public methods
	void attach(int minDeg, int maxDeg, int minPulse, int maxPulse);
	bool isLED();
	bool isServo();
	bool setPosition(uint8_t degree, int speed);
	int getMinDegree();
	int getMaxDegree();

private:
	// Private members
	uint8_t device;
	uint8_t i2cAddress;
	uint8_t expanderPin;

	ServoEasing* driver;
	bool LED;

	int pulseWidth0;
	int pulseWidth180;

	int MinDegree;
	int MaxDegree;


	// Private methods

};
/*****************************/
// Constructor Implementation
/*****************************/
/*================*/
// No Arguments - Set all private Variables to default values
/*================*/
SLDEVICE::SLDEVICE(uint8_t dev, uint8_t address, uint8_t pin, bool led) /*  : exampleVariable(0) */ {
	// Constructor code here
	LED = led;
	device = dev;
	i2cAddress = address;
	expanderPin = pin;
	driver = new ServoEasing(i2cAddress);
}
/********************************/
// Public Method Implementations
/********************************/
/*================*/
//
/*================*/
void SLDEVICE::attach(int minDeg, int maxDeg, int minPulse, int maxPulse) {
	// attach logic here
	pulseWidth0 = minPulse;
	if ((expanderPin == 15)) {
		Serial.println("attach pin 15");
		pulseWidth180 = LED_180_PULSE_WIDTH_LAST;
	}
	else pulseWidth180 = maxPulse;

	MinDegree = minDeg;
	MaxDegree = maxDeg;

	driver->attach(expanderPin, minDeg, minPulse, maxPulse);
}
/*================*/
//
/*================*/
bool SLDEVICE::isLED() {
	// is logic here
	return LED;
}
/*================*/
//
/*================*/
bool SLDEVICE::isServo() {
	// is logic here
	if (LED) return false;
	return true;
}
/*================*/
//
/*================*/
bool SLDEVICE::setPosition(uint8_t degree, int speed) {
	// is logic here
	driver->startEaseTo(degree, speed, START_UPDATE_BY_INTERRUPT);

}
/*================*/
//
/*================*/
int SLDEVICE::getMinDegree() {
	// is logic here
	return MinDegree;
}
/*================*/
//
/*================*/
int SLDEVICE::getMaxDegree() {
	// is logic here
	return MaxDegree;
}
/*===================================================================*/
/* Class: SLDEVICES                                                  */
/*===================================================================*/
class SLDEVICES {
public:
	// Constructor
	SLDEVICES();
	// Public methods
	begin();
	attach(uint8_t dev);
	bool isLED(uint8_t dev);
	bool setLED(uint8_t dev, uint8_t brightness, int speed);
	bool setServo(uint8_t dev, uint8_t degree, int speed);
	uint8_t maxDevices();
	bool synch();

private:
	// Private members
	uint8_t maxDevice;
	SLDEVICE* device[SLSERVOmax];

	// Private methods

};
/*****************************/
// Constructor Implementation
/*****************************/
/*================*/
// No Arguments - Set all private Variables to default values
/*================*/
SLDEVICES::SLDEVICES() /*  : exampleVariable(0) */ {
	// Constructor code here
	maxDevice = SLSERVOmax;

}
/********************************/
// Public Method Implementations
/********************************/
/*================*/
//
/*================*/
SLDEVICES::begin() {

	uint8_t pin = 0;
	uint8_t dev = 0;
	uint8_t i2cAddr = FIRST_PCA9685_EXPANDER_ADDRESS;
	// Define the servos
	for (uint8_t i = 0; i < MAX_SERVOS; i++) {
		device[dev] = new SLDEVICE(dev, i2cAddr, pin, false);
		dev++;
		pin++;
		if (pin > MAX_pin) {
			pin = 0;
			i2cAddr = SECOND_PCA9685_EXPANDER_ADDRESS;
		}
	}


	// Define the LEDs
	for (uint8_t i = 0; i < MAX_LEDS; i++) {
		device[dev] = new SLDEVICE(dev, i2cAddr, pin, true);
		dev++;
		pin++;
		if (pin > MAX_pin) {
			pin = 0;
			i2cAddr = SECOND_PCA9685_EXPANDER_ADDRESS;
		}
	}
}
/*================*/
//
/*================*/
SLDEVICES::attach(uint8_t dev) {
	if (device[dev]->isLED()) device[dev]->attach(MIN_LED_VALUE,MAX_LED_VALUE,LED_0_PULSE_WIDTH,LED_180_PULSE_WIDTH);
	else device[dev]->attach(MIN_DEGREE_VALUE,MAX_DEGREE_VALUE, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE);
}
/*================*/
//
/*================*/
bool SLDEVICES::isLED(uint8_t dev) {
	return device[dev]->isLED();
}
/*================*/
//
/*================*/
bool SLDEVICES::setLED(uint8_t dev,uint8_t brightness, int speed) {
	if (!isLED(dev)) return false;
	int range = device[dev]->getMaxDegree() - device[dev]->getMinDegree();
	int degree = range * (brightness / 100.0);
	Serial.print(" (");
	Serial.print(range);
	Serial.print("-");
	Serial.print(degree);
	Serial.print(" )");
	device[dev]->setPosition(degree, speed);

	return true;
}
/*================*/
//
/*================*/
bool SLDEVICES::setServo(uint8_t dev, uint8_t degree, int speed) {
	if (isLED(dev)) return false;
	device[dev]->setPosition(degree, speed);

	return true;
}
/*================*/
//
/*================*/
uint8_t SLDEVICES::maxDevices() {
	return maxDevice;
}
/*================*/
//
/*================*/
bool SLDEVICES::synch() {
	synchronizeAllServosStartAndWaitForAllServosToStop();
	return true;
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
SLDEVICES SLservos;
/******************************************************************************/
// 
/******************************************************************************/
/*==================*/
/*======================*/
// Library setup routine
/*======================*/
bool SLsetup() {
	// Start the Servo/LED driver system
	ServoEasing EasingTypeForAllServos(EASE_SINE_IN_OUT);

	SLservos.begin();

	for (uint8_t dev = 0; dev < SLSERVOmax; dev++) {
		SLservos.attach(dev);
	}

	return true; // Return true if successful
}
/******************************************************************************/
// End of Template Class
/******************************************************************************/
#endif // SLversion