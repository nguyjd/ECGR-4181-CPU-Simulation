#ifndef __ALU_H__
#define __ALU_H__

#include "Wire.h"
#include "Instruction.h"
#include <string>
#include <vector>

class ALU
{

public:

	ALU();
	ALU(Wire* inputA, Wire* inputB, Wire* inputALUOp, Wire* out, Wire* outFlag);

	// Connect the wires and checks if the config is valid.
	void ConnectInput1(Wire* wire);
	void ConnectInput2(Wire* wire);
	void ConnectInputALUOp(Wire* wire);
	void ConnectOutput(Wire* wire);
	void ConnectOutputFlag(Wire* wire);

	void ADDalu();
	void SUBalu();

	void Update();
	bool IsAdderConfigValid();

private:

	const char DATASIZE = 32;

	// Check if the size of the bus is correct and if the wires exist.
	bool CheckConnection();

	// True if the ALU is configured correctly.
	bool validConfig;

	// Helper Functions
	int StringToInt(std::string input);
	std::string IntTo32BitString(int input);

	// Data Wires
	Wire* input1, * input2, * ALUOp, * output, * outputFlag, * clkWire;

};

#endif