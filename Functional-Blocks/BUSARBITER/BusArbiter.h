#ifndef __BUSARBITER_H__
#define __BUSARBITER_H__

#include "Wire.h"

class BusArbiter
{

public:

	BusArbiter();

	void Update();

	void ConnectRequestLines(Wire* wire1, Wire* wire2, Wire* wire3, Wire* wire4);
	void ConnectGrantLines(Wire* wire1, Wire* wire2, Wire* wire3, Wire* wire4);
	void ConnectInterruptLines(Wire* wire1, Wire* wire2, Wire* wire3, Wire* wire4);
	void ConnectMemoryLines(Wire* bus, Wire* read, Wire* write, Wire* data);


private:

	Wire* requestLine1;
	Wire* requestLine2;
	Wire* requestLine3;
	Wire* requestLine4;

	Wire* grantLine1;
	Wire* grantLine2;
	Wire* grantLine3;
	Wire* grantLine4;

	Wire* interrupt1;
	Wire* interrupt2;
	Wire* interrupt3;
	Wire* interrupt4;

	// NOTE: the memBus is 36 bits.
	Wire* memBus;
	Wire* memRead;
	Wire* memWrite;
	Wire* memData;

};

#endif