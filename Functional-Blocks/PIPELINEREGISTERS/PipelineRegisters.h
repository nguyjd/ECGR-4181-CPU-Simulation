#ifndef __PIPELINEREGISTERS_H__
#define __PIPELINEREGISTERS_H__

#include "Wire.h"
#include "Data.h"
#include <vector>
#include <string>

class PipelineRegisters
{

public:
	PipelineRegisters();
	PipelineRegisters(Wire* clk);

	~PipelineRegisters();

	// Connect the wires and checks if the config is valid.
	void ConnectInputAndOutputPair(Wire* input, Wire* output);
	void ConnectCLK(Wire* wire);

	void Update();
	bool IsPRConfigValid();

private:

	const char DATASIZE = 32;
	const char CLKSIZE = 1;

	// Check if the size of the bus is correct and if the wires exist.
	bool CheckConnection();

	// True if the program counter is configured correctly.
	bool validConfig;

	// The datas are linked by index.
	std::vector<Wire*> registers;
	std::vector<Wire*> inputWires;
	std::vector<Wire*> outputWires;

	Wire* clkWire;


};

#endif