#include "Extend.h"

Extend::Extend()
{

	// Connect all wires
	inputWire = nullptr;
	outputWire = nullptr;
	inputBusSize = 0;
	outputBusSize = 0;

	validConfig = false;

}

Extend::Extend(Wire* input, Wire* output)
{

	// Set all the wires
	inputWire = input;
	outputWire = output;
	
	inputBusSize = inputWire->GetAmountofWires();
	outputBusSize = outputWire->GetAmountofWires();;

	// Check the config.
	validConfig = CheckConnection();

}

void Extend::ConnectInput(Wire* wire)
{

	inputWire = wire;
	inputBusSize = inputWire->GetAmountofWires();

	// Check the config.
	validConfig = CheckConnection();

}

void Extend::ConnectOutput(Wire* wire)
{

	outputWire = wire;
	outputBusSize = outputWire->GetAmountofWires();

	// Check the config.
	validConfig = CheckConnection();

}

bool Extend::IsExtendConfigValid()
{

	return validConfig;

}

bool Extend::CheckConnection()
{

	// Check the wire to see if they exist.
	if (!inputWire || !outputWire)
	{

		return false;

	}

	// Check all the bus size and check if the data is valid.
	if (inputWire->GetAmountofWires() != inputBusSize || !inputWire->IsWireDataValid())
	{

		return false;

	}
	if (outputWire->GetAmountofWires() != outputBusSize || !outputWire->IsWireDataValid())
	{

		return false;

	}

	// Check to see if the input is smaller than the output.
	if (inputBusSize >= outputBusSize)
	{

		return false;

	}

	return true;

}
