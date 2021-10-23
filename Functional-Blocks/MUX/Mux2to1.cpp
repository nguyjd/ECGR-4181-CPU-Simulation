#include "Mux2to1.h"

Mux2to1::Mux2to1()
{

	inputA = nullptr;
	inputB = nullptr;
	selectWire = nullptr;
	outputWire = nullptr;

	// Check the config.
	validConfig = CheckConnection();

}

Mux2to1::Mux2to1(Wire* a, Wire* b, Wire* select, Wire* output)
{

	// Set all the wires
	inputA = a;
	inputB = b;
	selectWire = select;
	outputWire = output;

	// Check the config.
	validConfig = CheckConnection();

}

void Mux2to1::ConnectInputA(Wire* wire)
{

	// Set the wire
	inputA = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Mux2to1::ConnectInputB(Wire* wire)
{

	// Set the wire
	inputB = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Mux2to1::ConnectSelect(Wire* wire)
{
	
	// Set the wire
	selectWire = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Mux2to1::ConnectOutput(Wire* wire)
{

	// Set the wire
	outputWire = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Mux2to1::Update()
{

	// Check the config before updating the data.
	if (validConfig)
	{

		// If the select line is zero, select A else select B
		std::string selectSignal = selectWire->GetWireDataStr();
		if (selectSignal.compare("0") == 0)
		{

			outputWire->SetWireData(inputA->GetWireDataStr());

		}
		// Assuming that the data is valid, the signal is '1'
		else
		{

			outputWire->SetWireData(inputB->GetWireDataStr());

		}

	}
	else
	{

		// Let the dev know that the something is wrong.
		std::cout << "A mux is misconfigured." << std::endl;

	}

}

bool Mux2to1::CheckConnection()
{
	
	// Check the wire to see if they exist.
	if (!inputA || !inputB || !selectWire || !outputWire)
	{

		return false;

	}

	// Check all the bus sizes.
	if (inputA->GetAmountofWires() != INPUTABITS)
	{

		return false;

	}
	if (inputB->GetAmountofWires() != INPUTBBITS)
	{

		return false;

	}
	if (selectWire->GetAmountofWires() != SELECTBITS)
	{

		return false;

	}
	if (outputWire->GetAmountofWires() != OUTPUTBITS)
	{

		return false;

	}

	// Pass all checks.
	return true;

}
