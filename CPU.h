#ifndef __CPU_H__
#define __CPU_H__

#include "Wire.h"
#include "LevelOneCache.h"


class CPU
{

public:
	CPU(Wire* memBus, Wire* request, Wire* grant, Wire* interrupt, Wire* halt, Wire* memData);
	~CPU();

	void Update();
	void CacheSnoop();

	void Read(std::string address);
	void Write(std::string address, std::string data);

private:

	int PC;

	Wire* memread;
	Wire* memwrite;
	Wire* memAddress;
	Wire* data;
	Wire* stall;
	Wire* haltLine;

	LevelOneCache* cache;

	// 2 bits - Bus Tranaction
	// 2 bits - State
	// 32 bits - Data
	const int MEMBUSSIZE = 36;

	// Used to feed the read and write response.
	std::vector<std::string> instr;
	std::vector<std::string> addresses;
	std::vector<std::string> instructionData;

};


#endif