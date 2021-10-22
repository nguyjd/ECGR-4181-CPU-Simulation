#include "Instruction.h"

Instruction::Instruction()
{

	validInstruction = false;
	instructionStr = "";

}

Instruction::Instruction(std::string inst)
{

	validInstruction = true;
	instructionStr = "";

	// Data Validation
	// Test to see if the instruction is 32-bits
	if (inst.length() != 32)
	{

		validInstruction = false;

	}

	// Test to see if there is any invalid chars
	for (int i = 0; i < 32; i++)
	{

		if (inst[i] != '0' && inst[i] != '1') 
		{ 
			
			validInstruction = false; 

		}

	}

	if (!validInstruction)
	{

		std::cout << "The instruction is invalid." << std::endl;

	}
	else
	{

		instructionStr = inst;

	}

}

void Instruction::SetInstruction(std::string inst)
{

	validInstruction = true;
	instructionStr = "";

	// Data Validation
	// Test to see if the instruction is 32-bits
	if (inst.length() != 32)
	{

		validInstruction = false;

	}

	// Test to see if there is any invalid chars
	for (int i = 0; i < 32; i++)
	{

		if (inst[i] != '0' && inst[i] != '1')
		{

			validInstruction = false;

		}

	}

	if (!validInstruction)
	{

		std::cout << "The instruction is invalid." << std::endl;

	}
	else
	{

		instructionStr = inst;

	}

}

std::string Instruction::GetInstructionStr()
{
	return instructionStr;
}

bool Instruction::IsInstructionValid()
{
	return validInstruction;
}
