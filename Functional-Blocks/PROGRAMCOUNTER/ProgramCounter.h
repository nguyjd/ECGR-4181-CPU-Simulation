#ifndef __PROGRAMCOUNTER_H__
#define __PROGRAMCOUNTER_H__

#include "Wire.h"
#include "Data.h"

class ProgramCounter
{

public:
	ProgramCounter();
	ProgramCounter(Wire* input, Wire* output, Wire* clk);

	~ProgramCounter();

	// Connect the wires and checks if the config is valid.
	void ConnectInput(Wire* wire);
	void ConnectOutput(Wire* wire);
	void ConnectCLK(Wire* wire);
	
	void Update();
	bool IsPCConfigValid();

private:

	const char DATASIZE = 32;
	const char CLKSIZE = 1;

	// Check if the size of the bus is correct and if the wires exist.
	bool CheckConnection();

	// True if the program counter is configured correctly.
	bool validConfig;

	Data* pcData;
	Wire* inputWire;
	Wire* outputWire;
	Wire* clkWire;
	

};

#endif
