#include "PipelineRegisters.h"

PipelineRegisters::PipelineRegisters()
{

	clkWire = nullptr;

	validConfig = CheckConnection();

}

PipelineRegisters::PipelineRegisters(Wire* clk)
{

	clkWire = clk;

	validConfig = CheckConnection();

}

PipelineRegisters::~PipelineRegisters()
{

	for (unsigned long long i = 0; i < registers.size(); i++)
	{

		delete registers[i];

	}

}

void PipelineRegisters::ConnectInputAndOutputPair(Wire* input, Wire* output)
{

	inputWires.push_back(input);
	outputWires.push_back(output);

	registers.push_back(new Wire(input->GetWireDataStr().size()));

}

void PipelineRegisters::ConnectCLK(Wire* wire)
{

	// Set the wire
	clkWire = wire;

	// Check if the wire is valid.
	validConfig = CheckConnection();

}

void PipelineRegisters::Update()
{
	
	validConfig = CheckConnection();
	if (validConfig)
	{


		for (unsigned long long i = 0; i < registers.size(); i++)
		{

			registers[i]->SetWireData(inputWires[i]->GetWireDataStr());

			// If the clk is high. The program counter is active high.
			if (clkWire->GetWireDataStr().compare("1") == 0)
			{

				outputWires[i]->SetWireData(registers[i]->GetWireDataStr());

			}

		}

	}
	else
	{

		// Let the dev know that the something is wrong.
		std::cout << "One of the pipeline registers is misconfigured or some data was invalid" << std::endl;

	}

}

bool PipelineRegisters::IsPRConfigValid()
{

	return validConfig;

}

bool PipelineRegisters::CheckConnection()
{

	// Check the wire to see if they exist.
	if (!clkWire)
	{

		return false;

	}

	for (unsigned long long i = 0; i < inputWires.size(); i++)
	{

		if (inputWires[i])
		{

			if (!inputWires[i]->IsWireDataValid())
			{

				return false;

			}

		}
		else
		{

			return false;

		}

	}

	for (unsigned long long i = 0; i < outputWires.size(); i++)
	{

		if (outputWires[i])
		{

			if (!outputWires[i]->IsWireDataValid())
			{

				return false;

			}

		}
		else
		{

			return false;

		}

	}

	for (unsigned long long i = 0; i < registers.size(); i++)
	{

		if (registers[i])
		{

			if (!registers[i]->IsWireDataValid())
			{
				
				return false;

			}

		}
		else
		{

			return false;

		}

	}

	//Check to see if the data are mismatched
	if (inputWires.size() != outputWires.size())
	{

		std::cout << "There is not a one to one mapping for the input and outputs." << std::endl;
		return false;

	}

	if (inputWires.size() != registers.size())
	{

		std::cout << "There is not a one to one mapping for the input and the internal data." << std::endl;
		return false;

	}

	return true;

}
