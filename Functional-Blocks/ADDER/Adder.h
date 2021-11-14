#ifndef __ADDER_H__
#define __ADDER_H__

#include "Wire.h"
#include "Instruction.h"
#include <string>
#include <vector>

class Adder
{

public:

	Adder();
	Adder(Wire* inputA, Wire* inputB, Wire* out);

	// Connect the wires and checks if the config is valid.
	void ConnectInput1(Wire* wire);
	void ConnectInput2(Wire* wire);
	void ConnectOutput(Wire* wire);

	void Update();
	bool IsAdderConfigValid();

private:

	const char DATASIZE = 32;

	// Check if the size of the bus is correct and if the wires exist.
	bool CheckConnection();

	// True if the program counter is configured correctly.
	bool validConfig;

	Wire *input1, *input2, *output;

};

#endif