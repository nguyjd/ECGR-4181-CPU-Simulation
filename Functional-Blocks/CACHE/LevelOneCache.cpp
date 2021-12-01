#include "LevelOneCache.h"

LevelOneCache::LevelOneCache(Wire* memaddress, Wire* read, Wire* write, Wire* bus)
{

	memoryAddress = memaddress;
	memRead = read;
	memWrite = write;

	memBusWire = bus;
	
	tagData = new Wire(TAGDATASIZE);
	indexData = new Wire(INDEXDATASIZE);
	offsetData = new Wire(OFFSETDATASIZE);

	for (int i = 0; i < BLOCKCOUNT; i++)
	{

		setOneTags.push_back(new Wire(STATESIZE + TAGDATASIZE));
		setTwoTags.push_back(new Wire(STATESIZE + TAGDATASIZE));

		std::vector<Wire*> data1;
		std::vector<Wire*> data2;
		for (int j = 0; j < BYTECOUNT / (MEMDATASIZE / 8); j++)
		{

			data1.push_back(new Wire(MEMDATASIZE));
			data2.push_back(new Wire(MEMDATASIZE));

		}

		setOne.push_back(data1);
		setTwo.push_back(data2);

	}

}

LevelOneCache::~LevelOneCache()
{

	delete tagData;
	delete indexData;
	delete offsetData;

	for (int i = 0; i < BLOCKCOUNT; i++)
	{

		delete setOneTags[i];
		delete setTwoTags[i];

		for (int j = 0; j < BYTECOUNT / (MEMDATASIZE / 8); j++)
		{

			delete setOne[i][j];
			delete setTwo[i][j];

		}

	}

}

void LevelOneCache::Update()
{

	// Split the address up.
	std::string address = memoryAddress->GetWireDataStr();
	tagData->SetWireData(address.substr(0, 19));
	indexData->SetWireData(address.substr(19, 9));
	offsetData->SetWireData(address.substr(28, 4));

	int blockIndex = BinaryToIndex(indexData);
	int blockOffset = BinaryToIndex(offsetData);
	int set = 0;

	// memRead is logical high.
	if (memRead->GetWireDataStr().compare("1") == 0)
	{

		std::string tag;
		std::string state;
		std::string data;

		// Select the set
		if (blockIndex % 2 == 0)
		{

			set = 1;

			// Get the index for the current set.
			blockIndex /= 2;
			
			tag = setOneTags[blockIndex]->GetWireDataStr();
			state = tag.substr(0, 2);
			data = setOne[blockIndex][blockOffset]->GetWireDataStr();

		}
		else
		{

			set = 2;

			// Get the index for the current set.
			blockIndex /= 2;

			tag = setTwoTags[blockIndex]->GetWireDataStr();
			state = tag.substr(0, 2);
			data = setTwo[blockIndex][blockOffset]->GetWireDataStr();

		}

		// Invalid state.
		if (state.compare("00") == 0)
		{

			std::cout << "READ MISS" << std::endl;
			std::cout << "The data in set " << set << ", block " << blockIndex << " with a offset of " << blockOffset << " is in a invalid state." << std::endl;
			std::cout << "State and Tag Data: " << tag << std::endl;
			std::cout << "Data: " << data << std::endl;
			std::cout << std::endl;

		}

		// Shared state.
		if (state.compare("01") == 0)
		{



		}

		// modified state.
		if (state.compare("10") == 0)
		{



		}

		// Exclusive state.
		if (state.compare("11") == 0)
		{



		}


	}

	// memWrite is logical high.
	if (memWrite->GetWireDataStr().compare("1") == 0)
	{

		

	}



}

int LevelOneCache::BinaryToIndex(Wire* wire)
{

	int poweroftwo = 1;
	int results = 0;
	std::string binNum = wire->GetWireDataStr();
	for (long long i = wire->GetAmountofWires() - 1; i >= 0; i--)
	{

		char num = binNum[i] - '0';

		results += num * poweroftwo;

		poweroftwo *= 2;

	}

	return results;

}
