#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "Event.h"
#include <time.h>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

class System
{

public:

	System() : eventProcessed(0) { srand(time(0)); }
	~System();

	// Print out the contents of the MEQ
	void PrintMEQ();
	
	// Create multiple events
	void GenerateEvents(int eventCount);
	
	// Process the event.
	void ReadEvent();

	int GetNumEventProcessed();

private:

	// Helper function to create the events.
	void GenerateEvent(time_t time, int integer);
	
	// Inserts the events and sorts the vector.
	void SortAndInsertMEQ(Event* event);

	// Vector to hold the events.
	std::vector<Event*> MEQ;

	// Amount of event read and processed.
	int eventProcessed;

};


#endif
