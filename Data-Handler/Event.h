#ifndef __EVENT_H__
#define __EVENT_H__

#include <time.h>
#include <string>

class Event
{

public:

	Event() : systemTime(0), inst(0) {}
	Event(time_t time, std::string number) : systemTime(time), inst(number) {}

	time_t GetTime() { return systemTime; };
	std::string GetString() { return inst; };

private:

	time_t systemTime;
	std::string inst;
	

};

#endif
