#ifndef __MUX4TO1_H__
#define __MUX4TO1_H__

#include "Wire.h"
#include <iostream>

class Mux4to1
{

public:

	Mux4to1();
	Mux4to1(Wire* a, Wire* b, Wire* c, Wire* d, Wire* select, Wire* output);

	// Connect the wire to the mux and checks if the config is valid.
	void ConnectInputA(Wire* wire);
	void ConnectInputB(Wire* wire);
	void ConnectInputC(Wire* wire);
	void ConnectInputD(Wire* wire);
	void ConnectSelect(Wire* wire);
	void ConnectOutput(Wire* wire);

	// Update the states of the wires.
	void Update();

	bool IsMuxConfigValid();

private:

	// The size of the bus of each wire.
	const long long DATASIZE = 32;
	const long long SELECTBITS = 2;

	// Check if the size of the bus is correct and if the wire exist.
	bool CheckConnection();

	// True if the mux is configured correctly.
	bool validConfig;

	// All the wire for the mux.
	Wire* inputA;
	Wire* inputB;
	Wire* inputC;
	Wire* inputD;
	Wire* selectWire;
	Wire* outputWire;

};


#endif