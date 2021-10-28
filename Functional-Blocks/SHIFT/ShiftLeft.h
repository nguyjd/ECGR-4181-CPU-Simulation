#ifndef __SHIFTLEFT_H__
#define __SHIFTLEFT_H__

#include "Wire.h"

class ShiftLeft
{

public:
	
	ShiftLeft();
	ShiftLeft(Wire* input, Wire* output, long long shiftCount);

	// Connect the wire and checks if the config is valid.
	void ConnectInput(Wire* wire);
	void ConnectOutput(Wire* wire);

	void Update();

	bool IsShiftConfigValid();

private:

	// Check if the size of the bus is correct and if the wire exist.
	bool CheckConnection();

	// True if the shift is configured correctly.
	bool validConfig;

	long long amountToShift;
	Wire* inputWire;
	Wire* outputWire;

	

};

#endif
