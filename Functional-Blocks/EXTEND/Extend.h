#ifndef __EXTEND_H__
#define __EXTEND_H__

#include "Wire.h"

class Extend
{

public:
	 
	Extend();
	Extend(Wire* input, Wire* output);

	// Connect the wire to the mux and checks if the config is valid.
	void ConnectInput(Wire* wire);
	void ConnectOutput(Wire* wire);

	virtual void Update() = 0;

	bool IsExtendConfigValid();

protected:

	// Check if the size of the bus is correct and if the wire exist.
	bool CheckConnection();

	// True if the extend is configured correctly.
	bool validConfig;

	long long inputBusSize;
	long long outputBusSize;
	Wire* inputWire;
	Wire* outputWire;

};

#endif