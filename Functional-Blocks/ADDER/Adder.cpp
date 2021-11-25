#include "Adder.h"

Adder::Adder()
{

	input1 = nullptr;
	input2 = nullptr;
	output = nullptr;

	validConfig = CheckConnection();

}

Adder::Adder(Wire* inputA, Wire* inputB, Wire* out)
{

	input1 = inputA;
	input2 = inputB;
	output = out;

	validConfig = CheckConnection();

}

void Adder::Update()
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

int Adder::StringToInt(std::string input)
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

std::string Adder::IntTo32BitString(int input)
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


void Adder::ConnectInput1(Wire* wire)
{

	// Set the wire
	input1 = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Adder::ConnectInput2(Wire* wire)
{

	// Set the wire
	input2 = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Adder::ConnectOutput(Wire* wire)
{

	// Set the wire
	output = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

bool Adder::IsAdderConfigValid()
{

	return validConfig;

}

bool Adder::CheckConnection()
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

	if (!output->IsWireDataValid() || output->GetAmountofWires() != DATASIZE)
	{

		return false;

	}

	return true;

}
