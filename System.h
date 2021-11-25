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
	
	// Process the event.
	std::string ReadEvent();

	int GetNumEventProcessed();

	// Helper function to create the events.
	void GenerateEvent(std::string instuction);


private:

	// Inserts the events and sorts the vector.
	void SortAndInsertMEQ(Event* event);

	// Vector to hold the events.
	std::vector<Event*> MEQ;

	// Amount of event read and processed.
	int eventProcessed;

};


#endif
