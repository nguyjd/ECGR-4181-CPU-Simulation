#ifndef __WIRE_H__
#define __WIRE_H__

#include "Data.h"

class Wire : private Data
{

public:
	Wire();
	Wire(std::string data);
	Wire(std::string data, long long int wireCount);

	// Set the data on the wires.
	void SetWireData(std::string data);

	// Resize the wire.
	void ResizeAmountofWires(long long int count);

	// Get the string and the width of the bus.
	std::string GetWireDataStr();
	long long int GetAmountofWires();

	// Return true if the data is valid.
	bool IsWireDataValid();

private:

	// Checks the wire data has any invalid char
	// and if the string size is the same size of the bus.
	bool DataValidation();

	// How wide the bus is.
	long long int numWire;

};


#endif