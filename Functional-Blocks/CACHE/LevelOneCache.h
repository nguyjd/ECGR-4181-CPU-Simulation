#ifndef __LEVELONECACHE_H__
#define __LEVELONECACHE_H__

#include "Wire.h"
#include <vector>

class LevelOneCache
{

public:

	LevelOneCache(Wire* memaddress, Wire* read, Wire* write, Wire* data, Wire* replace, Wire* request, Wire* grant, Wire* bus);
	~LevelOneCache();

	void Update();

	void Snoop();

	void ConnectInterrupt(Wire* wire);
	void ConnectWriteData(Wire* wire);


private:

	int BinaryToIndex(Wire* wire);
	std::string IntTo4BitString(int input);

	const int MEMDATASIZE = 32;
	const int BYTECOUNT = 64;
	const int SETS = 512;
	const int TAGDATASIZE = 19;
	const int INDEXDATASIZE = 9;
	const int OFFSETDATASIZE = 4;
	const int STATESIZE = 2;

	// To be connected
	Wire* memoryAddress;
	Wire* memRead;
	Wire* memWrite;
	Wire* memData;
	Wire* replaceBlock;
	Wire* requestWire;
	Wire* grantWire;
	Wire* memBus;
	Wire* interrupt;
	Wire* ramData;

	// Internal Wires
	Wire* tagData;
	Wire* indexData;
	Wire* offsetData;

	Wire* snoopTagData;
	Wire* snoopIndexData;
	Wire* snoopOffsetData;

	// Has tags and state bits
	std::vector<Wire*> blockOneTags;
	std::vector<Wire*> blockTwoTags;

	// Has the data
	std::vector<std::vector<Wire*>> blockOne;
	std::vector<std::vector<Wire*>> blockTwo;

	int lastUsedBlock;
	bool isBlockBeingReplaced;
	
	bool exclusiveState;
	bool sharedState;

	int blockOffset;
	int setIndex;

	int snoopBlockOffset;

	// RWITM - 11
	// MEM READ - 01
	// INVALIDATE - 10
	bool invalidateData;
	bool forceCopyBack;

};


#endif