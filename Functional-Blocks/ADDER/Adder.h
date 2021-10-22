#ifndef __ADDER_H__
#define __ADDER_H__

#include "Instruction.h"
#include <string>
#include <vector>

class Adder
{

public:
	Adder();
	Adder(std::string input1, std::string input2);

	void AddInputs(std::string input1, std::string input2);
	std::string OutputResult();

private:
	std::string input1, input2, output;

};

#endif