/******************************************************************************/
// File: LSinclude.h
// Project: ShowControl
// Description: LS (LED strip) include file
// Author: Bruce Fong
// Date: 2025-08-10
/******************************************************************************/
#if !defined(LSversion) // To ensure the header is included only once
#define LSversion 0.0
/******************************************************************************/
// Globals
/******************************************************************************/
/*===============*/
// Global Defines
/*===============*/
#define LS_DO 50			// LED string DO pin
#define LS_DO_PB 52			// Push button LED DO pin

#if !defined(LEDS_MAXBUTTONS)
#define LEDS_MAXBUTTONS 1
#endif
#if !defined(LEDS_MAXLEDS)
#define LEDS_MAXLEDS 100
#endif
#if !defined(LEDS_MAXSTRINGS)
#define LEDS_MAXSTRINGS 2
#endif

#define LEDS_type WS2811
#define LEDS_color_order GRB

#define LEDS_BRIGHTNESS 100
#define LEDS_fps 2000
/*===============-=*/
// Global Includes
/*================*/
#include <FastLED.h>
/*============================================================================*/
/******************************************************************************/
// Class Definition
/******************************************************************************/
class LSCLASS {
};
/*======================*/
// Library setup routine
/*======================*/
bool LSsetup() {
	// Start LS (LED STrip Driver)
#if defined(__DEBUG__)
	Serial.println("==> LSsetup called");
#endif

#if defined(__DEBUG__)
	Serial.println("<== LSsetup return");
#endif

}
/******************************************************************************/
// End of Template Class
/******************************************************************************/
#endif // LSversion

