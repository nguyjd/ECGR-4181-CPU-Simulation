#include "RegisterFile.h"

RegisterFile::RegisterFile()
{

	regOneLocation = nullptr;
	regTwoLocation = nullptr;
	writeEnable = nullptr;
	writeLocation = nullptr;
	writeData = nullptr;

	regOneOutput = nullptr;
	regTwoOutput = nullptr;

	// Fill the array with empty data.
	for (char i = 0; i < REGISTERCOUNT; i++)
	{

		registers.push_back(new Data());

	}


	// For assignment
	registers[2]->SetData("00000000000000000000000000010100");
	// For assignment
	registers[3]->SetData("00000000000000000000000000000010");

	validConfig = CheckConnection();

}

RegisterFile::RegisterFile(Wire* regOneInput, Wire* regTwoInput, Wire* outputOne, Wire* outputTwo, Wire* WE, Wire* writeReg, Wire* wData)
{

	regOneLocation = regOneInput;
	regTwoLocation = regTwoInput;
	writeEnable = WE;
	writeLocation = writeReg;
	writeData = wData;

	regOneOutput = outputOne;
	regTwoOutput = outputTwo;

	// Fill the array with empty data.
	for (char i = 0; i < REGISTERCOUNT; i++)
	{

		registers.push_back(new Data());

	}

	// For assignment
	registers[2]->SetData("00000000000000000000000000010100");
	// For assignment
	registers[3]->SetData("00000000000000000000000000000000");

	validConfig = CheckConnection();

}

RegisterFile::~RegisterFile()
{

	for (char i = 0; i < REGISTERCOUNT; i++)
	{

		delete registers.at(i);

	}

}

void RegisterFile::ConnectRegOneLocation(Wire* wire)
{

	// Set the wire
	regOneLocation = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void RegisterFile::ConnectRegTwoLocation(Wire* wire)
{

	// Set the wire
	regTwoLocation = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void RegisterFile::ConnectRegOneOutput(Wire* wire)
{

	// Set the wire
	regOneOutput = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void RegisterFile::ConnectRegTwoOutput(Wire* wire)
{

	// Set the wire
	regTwoOutput = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void RegisterFile::ConnectWriteEnable(Wire* wire)
{

	// Set the wire
	writeEnable = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void RegisterFile::ConnectWriteLocation(Wire* wire)
{

	// Set the wire
	writeLocation = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void RegisterFile::ConnectWriteData(Wire* wire)
{

	// Set the wire
	writeData = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void RegisterFile::PrintRegisters()
{

	if (!validConfig)
	{

		std::cout << "The register file is not configured correctly or bad data has somehow got into the registers. Data cannot be displayed." << std::endl;

	}
	else
	{

		std::cout << "REGISTER FILE CURRENT STATE" << std::endl;
		for (int i = 0; i < REGISTERCOUNT; i++)
		{

			std::cout << "X" << i << ":\t" << registers.at(i)->GetDataStr() << std::endl;

		}
		std::cout << "END OF THE REGISTER FILE" << std::endl;

	}
	

}

void RegisterFile::Update()
{
	validConfig = CheckConnection();
	if (validConfig)
	{

		// Find the correct index.
		char indexA = BinaryToIndex(regOneLocation->GetWireDataStr());
		char indexB = BinaryToIndex(regTwoLocation->GetWireDataStr());

		// Put the data from the register onto the wire.
		regOneOutput->SetWireData(registers[indexA]->GetDataStr());
		regTwoOutput->SetWireData(registers[indexB]->GetDataStr());

		// If the writeEnable signal is high.
		if (writeEnable->GetWireDataStr().compare("1") == 0)
		{

			// Find the correct index for the register
			char writeIndex = BinaryToIndex(writeLocation->GetWireDataStr());

			// Set the data for the register.
			registers[writeIndex]->SetData(writeData->GetWireDataStr());


		}

		// Hard wire the X0 to be all zeros
		registers[0]->SetData("00000000000000000000000000000000");


	}
	else
	{

		// Let the dev know that the something is wrong.
		std::cout << "The register file is misconfigured or some data was invalid" << std::endl;

	}

}

bool RegisterFile::IsRegFileConfigValid()
{

	return validConfig;

}

bool RegisterFile::CheckConnection()
{

	// Check the wire to see if they exist.
	if (!regOneLocation || !regTwoLocation || !writeEnable || !writeLocation || !writeData || !regOneOutput || !regTwoOutput)
	{

		return false;

	}

	// check if the data is valid.
	if (!regOneLocation->IsWireDataValid() || regOneLocation->GetAmountofWires() != REGLOCSIZE)
	{

		return false;

	}
	if (!regTwoLocation->IsWireDataValid() || regTwoLocation->GetAmountofWires() != REGLOCSIZE)
	{

		return false;

	}
	if (!writeEnable->IsWireDataValid() || writeEnable->GetAmountofWires() != WESIZE)
	{

		return false;

	}
	if (!writeLocation->IsWireDataValid() || writeLocation->GetAmountofWires() != REGLOCSIZE)
	{

		return false;

	}
	if (!writeData->IsWireDataValid() || writeData->GetAmountofWires() != DATASIZE)
	{

		return false;

	}
	if (!regOneOutput->IsWireDataValid() || regOneOutput->GetAmountofWires() != DATASIZE)
	{

		return false;

	}
	if (!regTwoOutput->IsWireDataValid() || regTwoOutput->GetAmountofWires() != DATASIZE)
	{

		return false;

	}

	// Check the register for valid data.
	for (char i = 0; i < REGISTERCOUNT; i++)
	{

		if (!registers.at(i)->IsDataValid())
		{

			return false;

		}

	}

	if (registers.at(0)->GetDataStr().compare("00000000000000000000000000000000") != 0)
	{

		return false;

	}

	return true;

}

char RegisterFile::BinaryToIndex(std::string bin)
{

	char poweroftwo = 1;
	char results = 0;
	for (char i = REGLOCSIZE - 1; i >= 0; i--)
	{

		char num = bin[i] - '0';
		
		results += num * poweroftwo;

		poweroftwo *= 2;

	}

	return results;

}
