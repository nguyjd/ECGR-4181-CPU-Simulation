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

		std::cout << "T: " << event->GetTime() << " | V: " << event->GetString() << std::endl;

	}

	std::cout << "-------------------------------" << std::endl;

}

std::string System::ReadEvent()
{

	// Get the pointer on top of the stack.
	if (!MEQ.empty())
	{

		Event* event = MEQ.front();
		std::string eventName = event->GetString();


		// Delete the old event.
		MEQ.erase(MEQ.begin());
		delete event;
		eventProcessed++;

		return eventName;

	}

	return "";

}

int System::GetNumEventProcessed()
{
	return eventProcessed;
}

void System::GenerateEvent(std::string instuction)
{

	// Create a new event.
	Event* event = new Event(time(0), instuction);
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
