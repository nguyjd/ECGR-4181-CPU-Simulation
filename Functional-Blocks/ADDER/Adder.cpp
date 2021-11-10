#include "Adder.h"

Adder::Adder()
{

	input1 = nullptr;
	input2 = nullptr;
	output = nullptr;

}

Adder::Adder(Wire* inputA, Wire* inputB, Wire* out)
{

	input1 = inputA;
	input2 = inputB;
	output = out;

}

std::string Adder::OutputResult()
{

	return output->GetWireDataStr();

}

void Adder::Update()
{

	// Temp Variables
	std::string tA = input1->GetWireDataStr();
	std::string tB = input2->GetWireDataStr();
	std::string tempOut = "00000000000000000000000000000000";
	char carry = 0;

	// Bitwise full-adder logic 
	for (int i = 31; i >= 0; i--)
	{

		char a = tA[i] - '0';
		char b = tB[i] - '0';

		tempOut[i] = ((a ^ b) ^ carry) + '0';

		carry = (a & b) || (carry & (a ^ b));

	}

	// Pushes result to output wire
	output->SetWireData(tempOut);

}

bool Adder::IsAdderConfigValid()
{

	// Check if input wires exist
	if (!input1 || !input2 || !output)
	{

		return false;

	}

	// Check if connection data is valid
	if (!input1->IsWireDataValid() || !input2->IsWireDataValid() || !output->IsWireDataValid())
	{

		return false;

	}

}