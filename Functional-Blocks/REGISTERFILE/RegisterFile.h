#ifndef __REGISTERFILE_H__
#define __REGISTERFILE_H__

#include "Wire.h"
#include <vector>
#include <iostream>

class RegisterFile
{

public:

	RegisterFile();
	RegisterFile(Wire* regOneInput, Wire* regTwoInput, Wire* outputOne, Wire* outputTwo, Wire* WE, Wire* writeReg, Wire* wData);

	// Delete all the pointers in the vector.
	~RegisterFile();
	
	// Connect the wires and checks if the config is valid.
	void ConnectRegOneLocation(Wire* wire);
	void ConnectRegTwoLocation(Wire* wire);
	void ConnectRegOneOutput(Wire* wire);
	void ConnectRegTwoOutput(Wire* wire);
	void ConnectWriteEnable(Wire* wire);
	void ConnectWriteLocation(Wire* wire);
	void ConnectWriteData(Wire* wire);

	void PrintRegisters();

	void Update();
	bool IsRegFileConfigValid();

private:

	const char REGISTERCOUNT = 32;
	const char REGLOCSIZE = 5;
	const char DATASIZE = 32;
	const char WESIZE = 1;

	// Check if the size of the bus is correct and if the wires exist.
	bool CheckConnection();

	// True if the register file is configured correctly.
	bool validConfig;

	// Convert the binary register location to an array index.
	char BinaryToIndex(std::string bin);

	std::vector<Data*> registers;

	Wire* regOneLocation;
	Wire* regTwoLocation;
	Wire* writeEnable;
	Wire* writeLocation;
	Wire* writeData;
	
	Wire* regOneOutput;
	Wire* regTwoOutput;

};

#endif