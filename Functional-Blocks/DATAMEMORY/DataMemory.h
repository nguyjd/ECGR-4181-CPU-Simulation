#ifndef __DATAMEMORY_H__
#define __DATAMEMORY_H__

#include "Wire.h"
#include <vector>

class DataMemory
{

public:
	DataMemory();
	DataMemory(Wire* size, Wire* read, Wire* write, Wire* inputdata, Wire* address,
			Wire* output8, Wire* output16, Wire* output32);

	~DataMemory();

	// Connect the wires and checks if the config is valid.
	void ConnectMemSize(Wire* wire);
	void ConnectMemRead(Wire* wire);
	void ConnectMemWrite(Wire* wire);
	void ConnectDataIn(Wire* wire);
	void ConnectMemAddress(Wire* wire);
	void ConnectOutputEightBits(Wire* wire);
	void ConnectOutputSixteenBits(Wire* wire);
	void ConnectOutputThirtyTwoBits(Wire* wire);

	void Update();
	bool IsDataMemoryConfigValid();

	void PrintMemory();

private:

	const unsigned long long MEMORYSIZE = 10000;

	// Check if the size of the bus is correct and if the wires exist.
	bool CheckConnection();

	// True if the program counter is configured correctly.
	bool validConfig;

	// Convert the binary register location to an array index.
	int BinaryToIndex(std::string bin);

	// Input Wires
	Wire* memSize;
	Wire* memRead;
	Wire* memWrite;
	Wire* dataIn;
	Wire* memAddress;

	// Output Wires
	Wire* outputEightBits;
	Wire* outputSixteenBits;
	Wire* outputThirtyTwoBits;

	std::vector<Wire*> ram;

};

#endif