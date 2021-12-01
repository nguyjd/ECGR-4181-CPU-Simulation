#ifndef __LEVELONECACHE_H__
#define __LEVELONECACHE_H__

#include "Wire.h"
#include <vector>

class LevelOneCache
{

public:

	LevelOneCache(Wire* memaddress, Wire* read, Wire* write, Wire* bus);
	~LevelOneCache();

	void Update();


private:

	int BinaryToIndex(Wire* wire);

	const int MEMDATASIZE = 32;

	const int BLOCKCOUNT = 512;
	const int BYTECOUNT = 64;
	const int SETS = 2;
	
	const int TAGDATASIZE = 20;
	const int INDEXDATASIZE = 9;
	const int OFFSETDATASIZE = 4;

	const int STATESIZE = 2;

	// 2 bits - Bus Tranaction
	// 2 bits - State
	// 32 bits - Data
	const int MEMBUSSIZE = 36;

	// To be connected
	Wire* memoryAddress;
	Wire* memRead;
	Wire* memWrite;
	Wire* memBusWire;

	// Internal Wires
	Wire* tagData;
	Wire* indexData;
	Wire* offsetData;

	// Has tags and state bits
	std::vector<Wire*> setOneTags;
	std::vector<Wire*> setTwoTags;

	// Has the data
	std::vector<std::vector<Wire*>> setOne;
	std::vector<std::vector<Wire*>> setTwo;

};


#endif