#include "Mux4to1.h"

Mux4to1::Mux4to1()
{

	// Set all the wires
	inputA = nullptr;
	inputB = nullptr;
	inputC = nullptr;
	inputD = nullptr;
	selectWire = nullptr;
	outputWire = nullptr;

	// Check the config.
	validConfig = CheckConnection();

}

Mux4to1::Mux4to1(Wire* a, Wire* b, Wire* c, Wire* d, Wire* select, Wire* output)
{

	// Set all the wires
	inputA = a;
	inputB = b;
	inputC = c;
	inputD = d;
	selectWire = select;
	outputWire = output;

	// Check the config.
	validConfig = CheckConnection();

}

void Mux4to1::ConnectInputA(Wire* wire)
{

	// Set the wire
	inputA = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Mux4to1::ConnectInputB(Wire* wire)
{

	// Set the wire
	inputB = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Mux4to1::ConnectInputC(Wire* wire)
{

	// Set the wire
	inputC = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Mux4to1::ConnectInputD(Wire* wire)
{

	// Set the wire
	inputD = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Mux4to1::ConnectSelect(Wire* wire)
{

	// Set the wire
	selectWire = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Mux4to1::ConnectOutput(Wire* wire)
{

	// Set the wire
	outputWire = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void Mux4to1::Update()
{

	// Check the config before updating the data.
	validConfig = CheckConnection();
	if (validConfig)
	{

		// Check the select signal
		std::string selectSignal = selectWire->GetWireDataStr();
		// Select A
		if (selectSignal.compare("00") == 0)
		{

			outputWire->SetWireData(inputA->GetWireDataStr());

		}
		// Select B
		else if (selectSignal.compare("01") == 0)
		{

			outputWire->SetWireData(inputB->GetWireDataStr());

		}
		// Select C
		else if (selectSignal.compare("10") == 0)
		{

			outputWire->SetWireData(inputC->GetWireDataStr());

		}
		// select signal should be 11, select D
		else
		{

			outputWire->SetWireData(inputD->GetWireDataStr());

		}

	}
	else
	{

		// Let the dev know that the something is wrong.
		std::cout << "A mux is misconfigured or data received was invalid" << std::endl;

	}

}

bool Mux4to1::IsMuxConfigValid()
{
	
	return validConfig;

}

bool Mux4to1::CheckConnection()
{

	// Check the wire to see if they exist.
	if (!inputA || !inputB || !inputC || !inputD || !selectWire || !outputWire)
	{

		return false;

	}

	// Check all the bus size and check if the data is valid.
	if (inputA->GetAmountofWires() != DATASIZE || !inputA->IsWireDataValid())
	{

		return false;

	}
	if (inputB->GetAmountofWires() != DATASIZE || !inputB->IsWireDataValid())
	{

		return false;

	}
	if (inputC->GetAmountofWires() != DATASIZE || !inputC->IsWireDataValid())
	{

		return false;

	}
	if (inputD->GetAmountofWires() != DATASIZE || !inputD->IsWireDataValid())
	{

		return false;

	}
	if (selectWire->GetAmountofWires() != SELECTBITS || !selectWire->IsWireDataValid())
	{

		return false;

	}
	if (outputWire->GetAmountofWires() != DATASIZE || !outputWire->IsWireDataValid())
	{

		return false;

	}

	// Pass all checks.
	return true;

}
