#include "ShiftLeft.h"

ShiftLeft::ShiftLeft()
{

	// Set all the wires
	inputWire = nullptr;
	outputWire = nullptr;
	amountToShift = 0;

	// Check the config.
	validConfig = CheckConnection();

}

ShiftLeft::ShiftLeft(Wire* input, Wire* output, long long shiftCount)
{

	// Set all the wires
	inputWire = input;
	outputWire = output;
	amountToShift = shiftCount;

	// Check the config.
	validConfig = CheckConnection();

}

void ShiftLeft::Update()
{

	validConfig = CheckConnection();
	if (validConfig)
	{

		// Push off the top bits
		std::string outputString = inputWire->GetWireDataStr().substr(amountToShift);
		
		// Add zeros to the end of the bit array.
		for (long long i = 0; i < amountToShift; i++)
		{

			outputString += "0";

		}

		// Push the data onto the wire.
		outputWire->SetWireData(outputString);

	}
	else
	{

		// Let the dev know that the something is wrong.
		std::cout << "A shift left is misconfigured or data received was invalid" << std::endl;

	}

}

bool ShiftLeft::IsShiftConfigValid()
{

	return validConfig;

}

bool ShiftLeft::CheckConnection()
{
	// Check the wire to see if they exist.
	if (!inputWire || !outputWire)
	{

		return false;

	}

	// check if the data is valid.
	if (!inputWire->IsWireDataValid())
	{

		return false;

	}
	if (!outputWire->IsWireDataValid())
	{

		return false;

	}

	// Check to see if the input is equal to the output.
	if (inputWire->GetAmountofWires() != outputWire->GetAmountofWires())
	{

		return false;

	}

	// Check to see if the amount of shift make sense.
	if (amountToShift < 0)
	{

		return false;

	}

	return true;
}
