#include "Adder.h"

Adder::Adder()
{
	input1 = "00000000000000000000000000000000";
	input2 = "00000000000000000000000000000000";
	output = "00000000000000000000000000000000";
	AddInputs(input1, input2);
}

Adder::Adder(std::string input1, std::string input2)
{
	output = "00000000000000000000000000000000";
	AddInputs(input1, input2);
}

std::string Adder::OutputResult()
{
	return output;
}

void Adder::AddInputs(std::string input1, std::string input2)
{
	char carry = 0;

	for (int i = 31; i >= 0; i--)
	{
		char a = input1[i] - '0';
		char b = input2[i] - '0';

		output[i] = ((a ^ b) ^ carry) + '0';

		carry = (a & b) || (carry & (a ^ b));
	}

}