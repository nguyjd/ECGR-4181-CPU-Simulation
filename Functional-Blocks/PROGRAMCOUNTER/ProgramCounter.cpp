#include "ProgramCounter.h"

ProgramCounter::ProgramCounter()
{

	inputWire = nullptr;
	outputWire = nullptr;
	clkWire = nullptr;
	pcData = new Data("00000000000000000000000000000000");

	validConfig = CheckConnection();

}

ProgramCounter::ProgramCounter(Wire* input, Wire* output, Wire* clk)
{

	inputWire = input;
	outputWire = output;
	clkWire = clk;
	pcData = new Data("00000000000000000000000000000000");

	validConfig = CheckConnection();

}

ProgramCounter::~ProgramCounter()
{

	delete pcData;

}

void ProgramCounter::ConnectInput(Wire* wire)
{

	// Set the wire
	inputWire = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void ProgramCounter::ConnectOutput(Wire* wire)
{

	// Set the wire
	outputWire = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void ProgramCounter::ConnectCLK(Wire* wire)
{

	// Set the wire
	clkWire = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void ProgramCounter::Update()
{

	validConfig = CheckConnection();
	if (validConfig)
	{

		pcData->SetData(inputWire->GetWireDataStr());

		// If the clk is high. The program counter is active high.
		if (clkWire->GetWireDataStr().compare("1") == 0)
		{

			outputWire->SetWireData(pcData->GetDataStr());

		}

	}
	else
	{

		// Let the dev know that the something is wrong.
		std::cout << "The program counter is misconfigured or some data was invalid" << std::endl;

	}

}

bool ProgramCounter::IsPCConfigValid()
{

	return validConfig;

}

bool ProgramCounter::CheckConnection()
{

	// Check the wire to see if they exist.
	if (!inputWire || !outputWire || !clkWire)
	{

		return false;

	}

	// check if the data is valid.
	if (!inputWire->IsWireDataValid() || inputWire->GetAmountofWires() != DATASIZE)
	{

		return false;

	}
	if (!outputWire->IsWireDataValid() || outputWire->GetAmountofWires() != DATASIZE)
	{

		return false;

	}
	if (!clkWire->IsWireDataValid() || clkWire->GetAmountofWires() != CLKSIZE)
	{

		return false;

	}
	if (!pcData->IsDataValid())
	{

		return false;

	}

	// Check the internal data
	if (pcData)
	{

		return pcData->IsDataValid();

	}
	else
	{

		return false;

	}

}
