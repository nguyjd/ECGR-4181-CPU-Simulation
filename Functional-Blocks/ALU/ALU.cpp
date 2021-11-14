#include "ALU.h"

ALU::ALU()
{

	input1 = nullptr;
	input2 = nullptr;
	output = nullptr;
	ALUOp = nullptr;
	outputBranch = nullptr;

	validConfig = CheckConnection();

}

ALU::ALU(Wire* inputA, Wire* inputB, Wire* inputALUOp, Wire* out, Wire* outFlag)
{

	input1 = inputA;
	input2 = inputB;
	output = out;
	ALUOp = inputALUOp;
	outputBranch = outFlag;

	validConfig = CheckConnection();

}

void ALU::Update() 
{

	if (ALUOp->GetWireDataStr().compare("00000") == 0)
	{
	
		ADDalu();
	
	}
	
	if (ALUOp->GetWireDataStr().compare("00001") == 0)
	{

		SUBalu();
	
	}

	// Load
	if (ALUOp->GetWireDataStr().compare("01111") == 0)
	{

		ADDalu();

	}

	// Store
	if (ALUOp->GetWireDataStr().compare("11011") == 0)
	{

		ADDalu();

	}

	// BNE
	if (ALUOp->GetWireDataStr().compare("10110") == 0)
	{

		BNEalu();

	}
	
}


int ALU::StringToInt(std::string input)
{

	int poweroftwo = 1;
	int results = 0;
	
	// Up to MSB
	for (int i = input.size() - 1; i > 0; i--)
	{

		char num = input[i] - '0';

		results += num * poweroftwo;

		poweroftwo *= 2;

	}

	results -= (input[0] * poweroftwo);

	return results;

}

std::string ALU::IntTo32BitString(int input)
{

	std::string binary = "";

	unsigned long long poweroftwo = 1;
	int results = input;
	for (int i = 1; i < 32; i++)
	{

		poweroftwo *= 2;

	}

	if (input < 0)
	{

		binary += '1';
		results += poweroftwo;

	}
	else
	{

		binary += '0';

	}

	poweroftwo /= 2;

	for (int i = 30; i >= 0; i--)
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


void ALU::ADDalu()
{

	// Temp Variables
	std::string tempOut = "00000000000000000000000000000000";
	char carry = 0;

	//Stores int equivalent of inputs
	int i_input1 = StringToInt(input1->GetWireDataStr());
	int i_input2 = StringToInt(input2->GetWireDataStr());

	int results = i_input1 + i_input2;

	// Pushes result to output wire
	output->SetWireData(IntTo32BitString(results));

}


void ALU::SUBalu()
{

	// Temp Variables
	std::string tempOut = "00000000000000000000000000000000";
	int i_tempOut = 0;
	char carry = 0;

	//Stores int equivalent of inputs
	int i_input1 = StringToInt(input1->GetWireDataStr());
	int i_input2 = StringToInt(input2->GetWireDataStr());

	i_tempOut = i_input2 - i_input1;

	tempOut = IntTo32BitString(i_tempOut);


	// Pushes result to output wire
	output->SetWireData(tempOut);

}

void ALU::BNEalu()
{

	int i_input1 = StringToInt(input1->GetWireDataStr());
	int i_input2 = StringToInt(input2->GetWireDataStr());

	if (i_input1 != i_input2)
	{

		outputBranch->SetWireData("1");

	}
	else
	{

		outputBranch->SetWireData("0");

	}

}

void ALU::ConnectInput1(Wire* wire)
{

	// Set the wire
	input1 = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void ALU::ConnectInput2(Wire* wire)
{

	// Set the wire
	input2 = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void ALU::ConnectInputALUOp(Wire* wire)
{

	// Set the wire
	ALUOp = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void ALU::ConnectOutput(Wire* wire)
{

	// Set the wire
	output = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void ALU::ConnectOutputFlag(Wire* wire)
{

	// Set the wire
	output = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

bool ALU::IsAdderConfigValid()
{

	return validConfig;

}

bool ALU::CheckConnection()
{

	// Check if input wires exist
	if (!input1 || !input2 || !output)
	{

		return false;

	}

	// Check if connection data is valid
	if (!input1->IsWireDataValid() || input1->GetAmountofWires() != DATASIZE)
	{

		return false;

	}

	if (!input2->IsWireDataValid() || input2->GetAmountofWires() != DATASIZE)
	{

		return false;

	}

	if (!ALUOp->IsWireDataValid() || input2->GetAmountofWires() != DATASIZE)
	{

		return false;

	}

	if (!output->IsWireDataValid() || output->GetAmountofWires() != DATASIZE)
	{

		return false;

	}

	return true;

}
