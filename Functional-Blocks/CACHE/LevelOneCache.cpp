#include "LevelOneCache.h"

LevelOneCache::LevelOneCache(Wire* memaddress, Wire* read, Wire* write, Wire* data, Wire* replace, Wire* request, Wire* grant, Wire* bus)
{

	memoryAddress = memaddress;
	memRead = read;
	memWrite = write;
	memData = data;
	replaceBlock = replace;
	requestWire = request;
	grantWire = grant;
	memBus = bus;
	
	tagData = new Wire(TAGDATASIZE);
	indexData = new Wire(INDEXDATASIZE);
	offsetData = new Wire(OFFSETDATASIZE);

	for (int i = 0; i < SETS; i++)
	{

		blockOneTags.push_back(new Wire(STATESIZE + TAGDATASIZE));
		blockTwoTags.push_back(new Wire(STATESIZE + TAGDATASIZE));

		std::vector<Wire*> data1;
		std::vector<Wire*> data2;
		for (int j = 0; j < BYTECOUNT / (MEMDATASIZE / 8); j++)
		{

			data1.push_back(new Wire(MEMDATASIZE));
			data2.push_back(new Wire(MEMDATASIZE));

		}

		blockOne.push_back(data1);
		blockTwo.push_back(data2);

	}

	lastUsedBlock = 1;
	isBlockBeingReplaced = false;
	exclusiveState = false;
	sharedState = false;

	blockOffset = 0;
	setIndex = 0;

	snoopBlockOffset = 0;

}

LevelOneCache::~LevelOneCache()
{

	delete tagData;
	delete indexData;
	delete offsetData;

	for (int i = 0; i < SETS; i++)
	{

		delete blockOneTags[i];
		delete blockTwoTags[i];

		for (int j = 0; j < BYTECOUNT / (MEMDATASIZE / 8); j++)
		{

			delete blockOne[i][j];
			delete blockTwo[i][j];

		}

	}

}

void LevelOneCache::Update()
{
	

	if (!isBlockBeingReplaced)
	{

		// Split the address up.
		std::string address = memoryAddress->GetWireDataStr();
		tagData->SetWireData(address.substr(0, TAGDATASIZE));
		indexData->SetWireData(address.substr(TAGDATASIZE, INDEXDATASIZE));
		offsetData->SetWireData(address.substr(TAGDATASIZE + INDEXDATASIZE, OFFSETDATASIZE));

		// Find the index.
		setIndex = BinaryToIndex(indexData);
		setIndex = setIndex % SETS;
		blockOffset = BinaryToIndex(offsetData);

		// for the output text - block number.
		int block = 0;

		// CPU want to read.
		if (memRead->GetWireDataStr().compare("1") == 0)
		{

			// For block 1
			std::string tag1;
			std::string state1;

			// For block 2
			std::string tag2;
			std::string state2;

			// For reading
			std::string state;
			std::string data;
			std::string tag;

			// Get the state and the tag from the block 1
			tag1 = blockOneTags[setIndex]->GetWireDataStr();
			state1 = tag1.substr(0, 2);
			tag1 = tag1.substr(2, -1);

			// Get the state and the tag from the block 2
			tag2 = blockTwoTags[setIndex]->GetWireDataStr();
			state2 = tag2.substr(0, 2);
			tag2 = tag2.substr(2, -1);

			if (tag1.compare(tagData->GetWireDataStr()) == 0 && state1.compare("00") != 0)
			{
				state = state1;
				data = blockOne[setIndex][blockOffset]->GetWireDataStr();
				tag = tagData->GetWireDataStr();

				block = 1;
				lastUsedBlock = 1;


			}
			else if (tag2.compare(tagData->GetWireDataStr()) == 0 && state2.compare("00") != 0)
			{

				state = state2;
				data = blockTwo[setIndex][blockOffset]->GetWireDataStr();
				tag = tagData->GetWireDataStr();

				block = 2;
				lastUsedBlock = 2;

			}
			else // Invalid state.
			{

				std::cout << "READ MISS" << std::endl;
				std::cout << "Cache: The data is in a invalid state." << std::endl;
				isBlockBeingReplaced = true;
				blockOffset = 0;

				replaceBlock->SetWireData("1");
				requestWire->SetWireData("1");

			}

			// Shared state.
			if (state.compare("01") == 0)
			{

				std::cout << "READ HIT" << std::endl;
				std::cout << "The data in set " << setIndex << ", block " << block << " with a offset of " << blockOffset << " is in a shared state." << std::endl;
				std::cout << "State and Tag Data: " << tag << std::endl;
				std::cout << "Data: " << data << std::endl;
				std::cout << "Cache: The state of the data is going from shared to shared" << std::endl;



			}

			// modified state.
			if (state.compare("10") == 0)
			{

				std::cout << "READ HIT" << std::endl;
				std::cout << "The data in set " << setIndex << ", block " << block << " with a offset of " << blockOffset << " is in a modified state." << std::endl;
				std::cout << "State and Tag Data: " << tag << std::endl;
				std::cout << "Data: " << data << std::endl;
				std::cout << "Cache: The state of the data is going from modified to modified" << std::endl;

			}

			// Exclusive state.
			if (state.compare("11") == 0)
			{

				std::cout << "READ HIT" << std::endl;
				std::cout << "The data in set " << setIndex << ", block " << block << " with a offset of " << blockOffset << " is in a exclusive state." << std::endl;
				std::cout << "State and Tag Data: " << state + tag << std::endl;
				std::cout << "Data: " << data << std::endl;
				std::cout << "Cache: The state of the data is going from exclusive to exclusive" << std::endl;

			}
			

		}

		// memWrite is logical high.
		if (memWrite->GetWireDataStr().compare("1") == 0)
		{
			



		}

	}
	// Replacing the block in the set on a READ MISS
	else
	{
		
		if (grantWire->GetWireDataStr().compare("1") == 0)
		{
			
			if (blockOffset > 16)
			{

				isBlockBeingReplaced = false;
				memBus->SetWireData("000000000000000000000000000000000000");
				replaceBlock->SetWireData("0");
				requestWire->SetWireData("0");
				blockOffset = BinaryToIndex(offsetData);
				

				if (exclusiveState)
				{

					std::cout << "Cache: The state of the data is going from Invalid to Exclusive" << std::endl;

				}

				if (sharedState)
				{

					std::cout << "Cache: The state of the data is going from Invalid to Shared" << std::endl;

				}

				if (lastUsedBlock == 1)
				{


					if (exclusiveState)
					{

						blockTwoTags[setIndex]->SetWireData("11" + tagData->GetWireDataStr());

					}
					else if (sharedState)
					{

						blockTwoTags[setIndex]->SetWireData("01" + tagData->GetWireDataStr());

					}

					std::cout << "State and Tag Data: " << blockTwoTags[setIndex]->GetWireDataStr() << std::endl;
					std::cout << "Data: " << blockTwo[setIndex][blockOffset]->GetWireDataStr() << std::endl;
					
					lastUsedBlock = 2;

				}
				else
				{

					if (exclusiveState)
					{

						blockOneTags[setIndex]->SetWireData("11" + tagData->GetWireDataStr());

					}
					else if (sharedState)
					{

						blockOneTags[setIndex]->SetWireData("01" + tagData->GetWireDataStr());

					}
					
					std::cout << "State and Tag Data: " << blockOneTags[setIndex]->GetWireDataStr() << std::endl;
					std::cout << "Data: " << blockOne[setIndex][blockOffset]->GetWireDataStr() << std::endl;
					lastUsedBlock = 1;

				}

				exclusiveState = false;
				sharedState = false;


			}
			else
			{

				if (blockOffset == 0)
				{

					// Place the information onto the bus.
					std::string address = tagData->GetWireDataStr() + indexData->GetWireDataStr() + IntTo4BitString(blockOffset);
					memBus->SetWireData("0100" + address);

				}
				else
				{

					std::string busData = memBus->GetWireDataStr();
					int setIndex = BinaryToIndex(indexData);

					// A cache has the memory.
					if (busData.substr(0, 2).compare("00") == 0)
					{

						sharedState = true;

					}
					// We have to pull from main memory.
					else 
					{

						exclusiveState = true;
						
					}

					if (lastUsedBlock == 1)
					{

						std::cout << "Cache: Storing data into block 2, Set " << setIndex << ", and block offset " << blockOffset - 1 << std::endl;
						blockTwo[setIndex][blockOffset - 1]->SetWireData(busData.substr(4, -1));

					}
					else
					{

						std::cout << "Cache: Storing data into block 1, Set " << setIndex << ", and block offset " << blockOffset - 1 << std::endl;
						blockOne[setIndex][blockOffset - 1]->SetWireData(busData.substr(4, -1));

					}

					std::string address = tagData->GetWireDataStr() + indexData->GetWireDataStr() + IntTo4BitString(blockOffset);
					memBus->SetWireData("0100" + address);



				}

				blockOffset += 1;

			}

		}
		else
		{
			
			std::cout << "Cache: Permission to write to the bus was not granted. The bus is busy." << std::endl;

			// INVERTER
			if (requestWire->GetWireDataStr().compare("1") == 0)
			{

				requestWire->SetWireData("0");

			}
			else
			{

				requestWire->SetWireData("1");

			}


		}

	}
	

}

void LevelOneCache::Snoop()
{

	std::string busTrans = memBus->GetWireDataStr().substr(0, 2);
	std::string state = memBus->GetWireDataStr().substr(2, 2);
	std::string address = memBus->GetWireDataStr().substr(4, -1);

	Wire* tagWire = new Wire(address.substr(0, TAGDATASIZE));
	Wire* indexWire = new Wire(address.substr(TAGDATASIZE, INDEXDATASIZE));
	Wire* offsetWire = new Wire(address.substr(TAGDATASIZE + INDEXDATASIZE, OFFSETDATASIZE));

	// Find the index.
	int setIndex = BinaryToIndex(indexWire);
	setIndex = setIndex % SETS;
	int blockOffset = BinaryToIndex(offsetWire);

	if (busTrans.compare("01") == 0)
	{

		bool foundValidData = false;
		int block = 0;

		// For block 1
		std::string tag1;
		std::string state1;

		// For block 2
		std::string tag2;
		std::string state2;

		// For reading
		std::string state;
		std::string data;

		// Get the state and the tag from the block 1
		tag1 = blockOneTags[setIndex]->GetWireDataStr();
		state1 = tag1.substr(0, 2);
		tag1 = tag1.substr(2, -1);

		// Get the state and the tag from the block 2
		tag2 = blockTwoTags[setIndex]->GetWireDataStr();
		state2 = tag2.substr(0, 2);
		tag2 = tag2.substr(2, -1);

		if (tag1.compare(tagData->GetWireDataStr()) == 0 && state1.compare("00") != 0)
		{
			
			foundValidData = true;
			data = blockOne[setIndex][blockOffset]->GetWireDataStr();
			state = state1;
			block = 1;


		}
		else if (tag2.compare(tagData->GetWireDataStr()) == 0 && state2.compare("00") != 0)
		{

			foundValidData = true;
			data = blockTwo[setIndex][blockOffset]->GetWireDataStr();
			state = state2;
			block = 2;

		}

		if (foundValidData)
		{

			snoopBlockOffset++;
			std::cout << "Cache(snooping): Found the set that a cache is looking for. Removing the memRead and dumping the data onto the bus." << std::endl;
			
			memBus->SetWireData("0001" + data);

		}
		else
		{

			snoopBlockOffset = 0;

		}

		if (snoopBlockOffset > 16)
		{

			// exclusive state
			if (state.compare("11") == 0)
			{

				std::cout << "Cache(snooping): The state of the data is going from exclusive to shared" << std::endl;

				if (block == 1)
				{

					blockOneTags[setIndex]->SetWireData("01" + tag1);

				}
				else if (block == 2)
				{

					blockTwoTags[setIndex]->SetWireData("01" + tag2);

				}



			}
			else if (state.compare("01") == 0)
			{

				std::cout << "Cache(snooping): The state of the data is going from shared to shared" << std::endl;

			}

		}


	}

	delete tagWire;
	delete indexWire;
	delete offsetWire;

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

std::string LevelOneCache::IntTo4BitString(int input)
{

	std::string binary = "";

	unsigned long long poweroftwo = 1;
	int results = input;
	for (int i = 1; i < 4; i++)
	{

		poweroftwo *= 2;

	}

	for (int i = 3; i >= 0; i--)
	{

		if (poweroftwo > results)
		{

			binary += '0';

		}
		else
		{

			binary += '1';
			results -= poweroftwo;

		}

		poweroftwo /= 2;

	}

	return binary;

}
