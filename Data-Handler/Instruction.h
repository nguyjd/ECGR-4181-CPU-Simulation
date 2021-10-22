#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <vector>
#include <string>
#include <iostream>

class Instruction
{

public:
	Instruction();
	Instruction(std::string inst);

    // Check the string for invalid setting such as not 32-bit
	void SetInstruction(std::string inst);

    // Return instruction as a string
	std::string GetInstructionStr();
	bool IsInstructionValid();

private:

    // True if the instruction is 32-bit
	bool validInstruction;
	std::string instructionStr;

};


#endif