/******************************************************************************/
// File: SCinclude.h
// Project: ShowControl2
// Description: SC (ShowControl) include file
// Author: Bruce Fong
// Date: 2025-07-10
/******************************************************************************/
#if !defined(SCversion) // To ensure the header is included only once
#define SCversion 0.0
/******************************************************************************/
// Globals
/******************************************************************************/
/*===============*/
// Global Defines
/*===============*/
#define SC_FRAME_RATE 20

#define SC_TIMER_INTERVAL_MS  10UL
#define SC_TIMER_INTERVAL_FRAME 50UL
#define SC_TIMER_INTERVAL_SEC  1000UL
/*================*/
// Global Includes
/*================*/
#define USE_TIMER_3 true
#include <TimerInterrupt.h>
#include <ISR_Timer.h>

/*============================================================================*/
/******************************************************************************/
// Class Definition
/******************************************************************************/
class SCTIMER {
public:
	//============
	// Constructor
	//============
	SCTIMER();
	//===============
	// Public methods
	//===============
	void setRemain(unsigned long seconds);
	void setElapsed(unsigned long seconds);
	void stopTimer();
	void startTimer();
	unsigned long getSecRemain();
	unsigned long getFrameRemain();
	unsigned long getSecElapsed();
	unsigned long getFrameElapsed();
	bool frameChanged(bool);
	bool secChanged(bool);
	String displaySecElapsed();
	//===============
	// Public members
	//===============
	volatile unsigned long sec_elapsed;		// Elapsed seconds (counts up) indendent of frame_elapsed
	volatile unsigned long frame_elapsed;	// Elapsed frames (counts up) independent of sec_elapsed
	volatile unsigned long sec_remain;		// Remaining seconds (counts down to 0) independent of frame_remaining - timer stops when count down to 0
	volatile unsigned long frame_remain;	// Remaining frames (counts down to 0) independent of sec_remaining - timer stops when count down to 0

	volatile bool running;					// timer running indicator
	volatile bool newFrame;					// new frame change indicator
	volatile bool newSec;					// new seconds change indicator
private:
	//================
	// Private members
	//================
	//================
	// Private methods
	//================

};
/*****************************/
// Constructor Implementation
/*****************************/
/*================*/
// No Arguments - Set all private Variables to default values
/*================*/
SCTIMER::SCTIMER() {
	// Constructor code here
	sec_elapsed = 0UL;		// Elapsed seconds (counts up) indendent of frame_elapsed
	frame_elapsed = 0UL;	// Elapsed frames (counts up) independent of sec_elapsed
	sec_remain = 0UL;		// Remaining seconds (counts down to 0) independent of frame_remaining - timer stops when count down to 0
	frame_remain = 0UL;	// Remaining frames (counts down to 0) independent of sec_remaining - timer stops when count down to 0

	running = false;		// timer running indicator
	newFrame = false;		// new frame change indicator
	newSec = false;			// new seconds change indicator
};
/********************************/
// Public Method Implementations
/********************************/
/*================*/
// setElapsed
/*================*/
void SCTIMER::setElapsed(unsigned long seconds) {
	// set logic here
	sec_elapsed = seconds;
	frame_elapsed = seconds * SC_FRAME_RATE;
	sec_remain = 0;
	frame_remain = 0;

	running = true;
}
/*================*/
// setRemain
/*================*/
void SCTIMER::setRemain(unsigned long seconds) {
	// set logic here
	sec_elapsed = 0;
	frame_elapsed = 0;
	sec_remain = seconds;
	frame_remain = seconds * SC_FRAME_RATE;

	running = true;
}
/*================*/
// stopTimer
/*================*/
void SCTIMER::stopTimer() {
	running = false;
}
/*================*/
// startTimer
/*================*/
void SCTIMER::startTimer() {
	running = true;
}
/*================*/
//
/*================*/
unsigned long SCTIMER::getSecRemain() {
	// get information logic here
	return sec_remain;
}
/*================*/
//
/*================*/
unsigned long SCTIMER::getFrameRemain() {
	// get information logic here
	return frame_remain;
}
/*================*/
//
/*================*/
unsigned long SCTIMER::getSecElapsed() {
	// get information logic here
	return sec_elapsed;
}
/*================*/
//
/*================*/
unsigned long SCTIMER::getFrameElapsed() {
	// get information logic here
	return frame_elapsed;
}
/*================*/
//
/*================*/
String SCTIMER::displaySecElapsed() {
	// display information logic here
	unsigned long dys = (sec_elapsed) / 86400UL;
	unsigned long hrs = (sec_elapsed - (dys * 86400UL)) / 3600UL;
	unsigned long min = (sec_elapsed - (dys * 86400UL) - (hrs * 3600UL)) / 60UL;
	unsigned long sec = (sec_elapsed - (dys * 86400UL) - (hrs * 3600UL) - (min * 60UL));

	String timeFmt = String(sec);
	if (sec < 10) timeFmt = "0" + timeFmt;
	timeFmt = String(min) + ":" + timeFmt;
	if (min < 10) timeFmt = "0" + timeFmt;
	if ((hrs > 0) || (dys > 0)) {
		timeFmt = String(hrs) + ":" + timeFmt;
		if (hrs < 10) timeFmt = "0" + timeFmt;
		if (dys > 0) {
			timeFmt = String(dys) + ":" + timeFmt;
			if (dys < 10) timeFmt = "0" + timeFmt;
		}
	}

	return timeFmt;
}
/*================*/
//
/*================*/
bool SCTIMER::frameChanged(bool reset) {
	// frameChanged logic here
	if (!newFrame) return false;
	if (reset) newFrame = false;
	return true;
}
/*================*/
//
/*================*/
bool SCTIMER::secChanged(bool reset) {
	// secondChanged logic here
	if (!newSec) return false;
	if (reset) newSec = false;
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
SCTIMER scClock_RT; // Realtime clock
SCTIMER scClock_ST; // Showtime clock

ISR_Timer scISR_timer;
/******************************************************************************/
// 
/******************************************************************************/
//===================
//
//===================
void SCTimerHandler() {
	scISR_timer.run();
}
//===================
//
//===================
void SCframe_tick() {
	// Process a frame tick
	// RT - RealTime Clock
	if (scClock_RT.running) {
		scClock_RT.frame_elapsed++;
		scClock_RT.newFrame = true;
		if (scClock_RT.frame_remain > 0) {
			scClock_RT.frame_remain--;
			if (scClock_RT.frame_remain == 0) scClock_RT.running = false;
		}
	}
	// ST - ShowTime Clock
	if (scClock_ST.running) {
		scClock_ST.frame_elapsed++;
		scClock_ST.newFrame = true;
		if (scClock_ST.frame_remain > 0) {
			scClock_ST.frame_remain--;
			if (scClock_ST.frame_remain == 0) scClock_ST.running = false;
		}
	}
}
//===================
//
//===================
void SCsec_tick() {
	// Process a sec tick
	// RT - RealTime Clock
	if (scClock_RT.running) {
		scClock_RT.sec_elapsed++;
		scClock_RT.newSec = true;
		if (scClock_RT.sec_remain > 0) {
			scClock_RT.sec_remain--;
			if (scClock_RT.sec_remain == 0) scClock_RT.running = false;
		}
	}
	// ST - ShowTime Clock
	if (scClock_ST.running) {
		scClock_ST.sec_elapsed++;
		scClock_ST.newSec = true;
		if (scClock_ST.sec_remain > 0) {
			scClock_ST.sec_remain--;
			if (scClock_ST.sec_remain == 0) scClock_ST.running = false;
		}
	}
}
/*======================*/
// Library setup routine
/*======================*/
bool SCsetup() {
	//===============================//
	// Start initialization
	//===============================//
#if defined(__DEBUG__)
	Serial.println("== SCstart begin");
#endif
	//===============================//
	// ISR Timers setup
	//===============================//
	ITimer3.init();
	ITimer3.attachInterruptInterval(SC_TIMER_INTERVAL_MS, SCTimerHandler);

	scISR_timer.setInterval(SC_TIMER_INTERVAL_FRAME, SCframe_tick);
	scISR_timer.setInterval(SC_TIMER_INTERVAL_SEC, SCsec_tick);
	//===============================//
	// Start the Reat Time Clock
	//===============================//
	scClock_RT.setElapsed(86400UL - 10);
	//===============================//
	// Return
	//===============================//
#if defined(__DEBUG__)
	Serial.println("== SCstart end");
#endif
	return true; // Return true if successful
}
/******************************************************************************/
// End of Template Class
/******************************************************************************/
#endif // SCversion