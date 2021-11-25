#include "Instruction.h"

void Instruction::SetInstruction(std::string inst)
{

	dataStr = inst;
	validData = DataValidation();

}

std::string Instruction::GetInstructionStr()
{
	return dataStr;
}

bool Instruction::IsInstructionValid()
{
	return validData;
}
