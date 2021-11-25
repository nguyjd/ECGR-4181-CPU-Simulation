#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "Data.h"

class Instruction : private Data 
{

public:
	Instruction() : Data() {}
	Instruction(std::string inst) : Data(inst) {}

	// Set the instruction.
	void SetInstruction(std::string inst);

	// Get the instruction string
	std::string GetInstructionStr();

	// Return true if the instruction valid.
	bool IsInstructionValid();

};


#endif