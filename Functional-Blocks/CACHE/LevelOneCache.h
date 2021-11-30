#ifndef __LEVELONECACHE_H__
#define __LEVELONECACHE_H__

#include "Wire.h"
#include <vector>

enum MemState
{

	Invalid,
	Modified,
	Shared,
	Exclusive

};

class LevelOneCache
{

public:

	LevelOneCache();
	~LevelOneCache();


private:

	const int MEMDATASIZE = 32;

	const int BLOCKCOUNT = 512;
	const int SETS = 2;
	
	const int TAGDATASIZE = 17;
	const int INDEXDATASIZE = 9;
	const int OFFSETDATASIZE = 6;

	// 2 bits - Bus Tranaction
	// 2 bits - State
	// 32 bits - Data
	const int MEMBUSSIZE = 36;

	//Wire* memBusWire;

	// Internal Wires
	Wire* tagData;
	Wire* indexData;
	Wire* offsetData;

	// Has tags and valid bit
	std::vector<Wire*> setOneTags;
	std::vector<Wire*> setTwoTags;

	// Has the data
	std::vector<Wire*> setOne;
	std::vector<Wire*> setTwo;

};


#endif