#include "ALU.h"

ALU::ALU()
{

	input1 = nullptr;
	input2 = nullptr;
	output = nullptr;
	ALUOp = nullptr;
	outputFlag = nullptr;

	validConfig = CheckConnection();

}

ALU::ALU(Wire* inputA, Wire* inputB, Wire* inputALUOp, Wire* out, Wire* outFlag)
{

	input1 = inputA;
	input2 = inputB;
	output = out;
	ALUOp = inputALUOp;
	outputFlag = outFlag;

	validConfig = CheckConnection();

}

void ALU::Update() 
{

	if ((ALUOp->GetWireDataStr()) == "00000")
	{
		ADDalu();
	}
	else if ((ALUOp->GetWireDataStr()) == "00001")
	{
		SUBalu();
	}
	
}


int StringToInt(std::string input)
{
	return std::stoi(input, nullptr, 2);
}

std::string IntTo32BitString(int input) 
{
	std::string binary = "";
	int bitmask = 1;
	for (int i = 0; i < 31; i++)
	{
		if ((bitmask & input) >= 1)
			binary = "1" + binary;
		else
			binary = "0" + binary;
		bitmask <<= 1;
	}
	return binary;
}


void ALU::ADDalu()
{

	// Temp Variables
	std::string tempOut = "00000000000000000000000000000000";
	char carry = 0;

	// Bitwise full-adder logic 
	for (int i = 31; i >= 0; i--)
	{

		char a = input1->GetWireDataStr()[i] - '0';
		char b = input2->GetWireDataStr()[i] - '0';

		tempOut[i] = ((a ^ b) ^ carry) + '0';

		carry = (a & b) || (carry & (a ^ b));

	}

	// Pushes result to output wire
	output->SetWireData(tempOut);

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

	int i_tempOut = i_input2 - i_input1;

	tempOut = IntTo32BitString(i_tempOut);


	// Pushes result to output wire
	output->SetWireData(tempOut);

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
