#ifndef __EVENT_H__
#define __EVENT_H__

#include <time.h>

class Event
{

public:

	Event() : systemTime(0), randomInteger(0) {}
	Event(time_t time, int number) : systemTime(time), randomInteger(number) {}

	time_t GetTime() { return systemTime; };
	int GetInteger() { return randomInteger; };

private:

	time_t systemTime;
	int randomInteger;
	

};

#endif
