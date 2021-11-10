#ifndef __ADDER_H__
#define __ADDER_H__

#include "Wire.h"
#include "Instruction.h"
#include <string>
#include <vector>

class Adder
{

public:

	Adder();
	Adder(Wire* inputA, Wire* inputB, Wire* out);

	void Update();
	std::string OutputResult();

	bool IsAdderConfigValid();

private:

	Wire *input1, *input2, *output;

};

#endif