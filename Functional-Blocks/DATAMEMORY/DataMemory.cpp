#include "DataMemory.h"

DataMemory::DataMemory()
{

	memSize = nullptr;
	memRead = nullptr;
	memWrite = nullptr;
	dataIn = nullptr;
	memAddress = nullptr;
	outputEightBits = nullptr;
	outputSixteenBits = nullptr;
	outputThirtyTwoBits = nullptr;

	for (unsigned long long i = 0; i < MEMORYSIZE; i++)
	{

		ram.push_back(new Wire(8));

	}

	validConfig = CheckConnection();

}

DataMemory::DataMemory(Wire* size, Wire* read, Wire* write, Wire* inputdata, Wire* address, Wire* output8, Wire* output16, Wire* output32)
{

	memSize = size;
	memRead = read;
	memWrite = write;
	dataIn = inputdata;
	memAddress = address;
	outputEightBits = output8;
	outputSixteenBits = output16;
	outputThirtyTwoBits = output32;

	for (unsigned long long i = 0; i < MEMORYSIZE; i++)
	{

		ram.push_back(new Wire(8));

	}

	validConfig = CheckConnection();

}

DataMemory::~DataMemory()
{

	for (unsigned long long i = 0; i < MEMORYSIZE; i++)
	{

		delete ram[i];

	}

}

void DataMemory::ConnectMemSize(Wire* wire)
{

	// Set the wire
	memSize = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void DataMemory::ConnectMemRead(Wire* wire)
{

	// Set the wire
	memRead = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void DataMemory::ConnectMemWrite(Wire* wire)
{

	// Set the wire
	memWrite = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void DataMemory::ConnectDataIn(Wire* wire)
{

	// Set the wire
	dataIn = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void DataMemory::ConnectMemAddress(Wire* wire)
{

	// Set the wire
	memAddress = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void DataMemory::ConnectOutputEightBits(Wire* wire)
{

	// Set the wire
	outputEightBits = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void DataMemory::ConnectOutputSixteenBits(Wire* wire)
{

	// Set the wire
	outputSixteenBits = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void DataMemory::ConnectOutputThirtyTwoBits(Wire* wire)
{

	// Set the wire
	outputThirtyTwoBits = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void DataMemory::Update()
{

	validConfig = CheckConnection();
	if (validConfig)
	{

		int indexLoc = BinaryToIndex(memAddress->GetWireDataStr());

		// memRead is logical high.
		if (memRead->GetWireDataStr().compare("1") == 0)
		{

			// eight bits
			if (memSize->GetWireDataStr().compare("00") == 0)
			{

				outputEightBits->SetWireData(ram[indexLoc]->GetWireDataStr());

			}

			// sixteen bits
			if (memSize->GetWireDataStr().compare("01") == 0)
			{

				std::string data = "";
				data += ram[indexLoc + 1]->GetWireDataStr();
				data += ram[indexLoc]->GetWireDataStr();

				outputSixteenBits->SetWireData(data);

			}

			// Thirty Two bits
			if (memSize->GetWireDataStr().compare("10") == 0)
			{

				std::string data = "";
				data += ram[indexLoc + 3]->GetWireDataStr();
				data += ram[indexLoc + 2]->GetWireDataStr();
				data += ram[indexLoc + 1]->GetWireDataStr();
				data += ram[indexLoc]->GetWireDataStr();

				outputThirtyTwoBits->SetWireData(data);

			}

		}

		// memWrite is logical high.
		if (memWrite->GetWireDataStr().compare("1") == 0)
		{

			std::string byte1 = dataIn->GetWireDataStr().substr(0, 8);
			std::string byte2 = dataIn->GetWireDataStr().substr(8, 8);
			std::string byte3 = dataIn->GetWireDataStr().substr(16, 8);
			std::string byte4 = dataIn->GetWireDataStr().substr(24, 8);

			// eight bits
			if (memSize->GetWireDataStr().compare("00") == 0)
			{

				ram[indexLoc]->SetWireData(byte4);

			}

			// sixteen bits
			if (memSize->GetWireDataStr().compare("01") == 0)
			{

				ram[indexLoc]->SetWireData(byte4);
				ram[indexLoc + 1]->SetWireData(byte3);


			}

			// Thirty Two bits
			if (memSize->GetWireDataStr().compare("10") == 0)
			{

				ram[indexLoc]->SetWireData(byte4);
				ram[indexLoc + 1]->SetWireData(byte3);
				ram[indexLoc + 2]->SetWireData(byte2);
				ram[indexLoc + 3]->SetWireData(byte1);

			}

		}

	}

}

bool DataMemory::IsDataMemoryConfigValid()
{

	return validConfig;

}

void DataMemory::PrintMemory()
{

	if (!validConfig)
	{

		std::cout << "The DataMemory is not configured correctly or bad data has somehow got into the registers. Data cannot be displayed." << std::endl;

	}
	else
	{

		std::cout << "DataMemory CURRENT STATE" << std::endl;
		for (int i = 0; i < MEMORYSIZE; i++)
		{

			std::cout << "X" << i << ":\t" << ram.at(i)->GetWireDataStr() << std::endl;

		}
		std::cout << "END OF THE DataMemory" << std::endl;

	}

}

bool DataMemory::CheckConnection()
{

	// Check the wire to see if they exist.
	if (!memSize || !memRead || !memWrite || !dataIn || !memAddress)
	{

		return false;

	}

	if (!outputEightBits || !outputSixteenBits || !outputThirtyTwoBits)
	{

		return false;

	}

	if (!memSize->IsWireDataValid() || memSize->GetAmountofWires() != 2)
	{

		return false;

	}

	if (!memRead->IsWireDataValid() || memRead->GetAmountofWires() != 1)
	{

		return false;

	}

	if (!memWrite->IsWireDataValid() || memWrite->GetAmountofWires() != 1)
	{

		return false;

	}

	if (!dataIn->IsWireDataValid() || dataIn->GetAmountofWires() != 32)
	{

		return false;

	}

	if (!memAddress->IsWireDataValid() || memAddress->GetAmountofWires() != 32)
	{

		return false;

	}

	if (!outputEightBits->IsWireDataValid() || outputEightBits->GetAmountofWires() != 8)
	{

		return false;

	}

	if (!outputSixteenBits->IsWireDataValid() || outputSixteenBits->GetAmountofWires() != 16)
	{

		return false;

	}

	if (!outputThirtyTwoBits->IsWireDataValid() || outputThirtyTwoBits->GetAmountofWires() != 32)
	{

		return false;

	}

	// Check the ram for invalid data
	for (unsigned long long i = 0; i < MEMORYSIZE; i++)
	{

		if (!ram[i]->IsWireDataValid())
		{

			return false;

		}

	}

	return true;

}

int DataMemory::BinaryToIndex(std::string bin)
{

	int poweroftwo = 1;
	int results = 0;
	for (long long i = memAddress->GetAmountofWires() - 1; i >= 0; i--)
	{

		char num = bin[i] - '0';

		results += num * poweroftwo;

		poweroftwo *= 2;

	}

	return results;

}