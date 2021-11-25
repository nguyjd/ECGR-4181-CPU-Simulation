#include "ZeroExtend.h"

void ZeroExtend::Update()
{

	// Check the config before updating the data.
	validConfig = CheckConnection();
	if (validConfig)
	{

		std::string outputString = inputWire->GetWireDataStr();
		// Extend the bits.
		for (long long i = inputBusSize; i < outputBusSize; i++)
		{

			outputString = "0" + outputString;

		}

		// Push the data onto the wire.
		outputWire->SetWireData(outputString);

	}
	else
	{

		// Let the dev know that the something is wrong.
		std::cout << "A zero extend is misconfigured or data received was invalid" << std::endl;

	}

}
