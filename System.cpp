#include "System.h"

System::~System()
{

	// Deletes the rest of the pointers to avoid memory leaks.
	for (auto event : MEQ)
	{

		delete event;

	}

	// Clear the vector.
	MEQ.clear();
	
}

void System::PrintMEQ()
{

	std::cout << "--------------MEQ--------------" << std::endl;

	// Print out MEQ
	for (auto event : MEQ)
	{

		std::cout << "T: " << event->GetTime() << " | V: " << event->GetInteger() << std::endl;

	}

	std::cout << "-------------------------------" << std::endl;

}

void System::GenerateEvents(int eventCount)
{

	// Generate the Events based on the amount of events given.
	for (int i = 0; i < eventCount; i++)
	{

		// Get the current time.
		time_t seconds = time(0);

		GenerateEvent(seconds, rand());

		// Delay for one second.
		time_t currentTime = time(0);
		while (seconds == currentTime)
		{

			currentTime = time(0);

		}

	}

}

void System::ReadEvent()
{

	// Get the pointer on top of the stack.
	Event* event = MEQ.front();

	// Store the values of the event.
	time_t newTime = event->GetTime() + rand();
	int integer = event->GetInteger();

	// Print out the integer from the event.
	std::cout << "V: " << integer << std::endl;

	// Make a new event.
	GenerateEvent(newTime, integer);

	// Delete the old event.
	MEQ.erase(MEQ.begin());
	delete event;
	eventProcessed++;

}

int System::GetNumEventProcessed()
{
	return eventProcessed;
}

void System::GenerateEvent(time_t time, int integer)
{

	// Create a new event.
	Event* event = new Event(time, integer);
	SortAndInsertMEQ(event);


}

void System::SortAndInsertMEQ(Event* event)
{

	// Add the event into the vector.
	MEQ.push_back(event);

	
	// Sort the vector based on time with insertion Sort
	for (int i = 1; i < MEQ.size(); i++)
	{

		Event* temp = MEQ.at(i);
		int index = i;

		while ((index > 0) && (MEQ.at(index - 1)->GetTime() > temp->GetTime()))
		{

			MEQ.at(index) = MEQ.at(index - 1);
			index--;

		}

		MEQ.at(index) = temp;

	}


}
