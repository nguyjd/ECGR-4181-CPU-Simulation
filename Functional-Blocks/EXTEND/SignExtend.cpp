#include "SignExtend.h"

void SignExtend::Update()
{

	// Check the config before updating the data.
	validConfig = CheckConnection();
	if (validConfig)
	{

		std::string outputString = inputWire->GetWireDataStr();
		
		// Find the sign
		char MSB = outputString[0];
		// Extend the bits.
		for (long long i = inputBusSize; i < outputBusSize; i++)
		{

			outputString = MSB + outputString;

		}

		// Push the data onto the wire.
		outputWire->SetWireData(outputString);

	}
	else
	{

		// Let the dev know that the something is wrong.
		std::cout << "A sign extend is misconfigured or data received was invalid" << std::endl;

	}

}
