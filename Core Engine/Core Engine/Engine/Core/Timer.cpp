#include "Timer.h"



Timer::Timer() 
{
	prevTicks = 0;
	currentTicks = 0;
}


Timer::~Timer()
{
}

void Timer::Start() {
	prevTicks = SDL_GetTicks();
	currentTicks = SDL_GetTicks();

}

void Timer::UpdateFrameTicks() {
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();

}

float Timer::GetDeltaTime() const {
	return (float)((currentTicks - prevTicks) / 1000.0f);
}

unsigned int Timer::GetSleepTime(const unsigned int fps_)const {
	unsigned int milliSecsperFrame = 1000 / fps_;
	if (milliSecsperFrame == 0) {
		return 0;
	}
	unsigned int sleepTime = milliSecsperFrame - SDL_GetTicks();
	if (sleepTime > milliSecsperFrame) {
		return milliSecsperFrame;
	}
	return sleepTime;
	
}

float Timer::GetCurrentTicks()const {
	return (float)currentTicks / 1000.0f;
}


