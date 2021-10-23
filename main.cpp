#include <iostream>
#include <Adder.h>
#include "Mux2to1.h"
#include "Mux4to1.h"


int main()
{
	std::string in1 = "00000000000000000000000000000001";
	std::string in2 = "00000000000000000000000000000101";


	Adder *adda = new Adder(in1, in2);
	std::cout << adda->OutputResult() << std::endl;

	Wire* inputA = new Wire("00000000000000000000000000000001");
	Wire* inputB = new Wire("00000000000000000000000000000011");
	Wire* inputC = new Wire("00000000000000000000000000000111");
	Wire* inputD = new Wire("00000000000000000000000000001111");
	Wire* select = new Wire("00");
	Wire* output = new Wire(32);

	Mux4to1* mux1 = new Mux4to1(inputA, inputB, inputC, inputD, select, output);
	mux1->Update();

	if (output->IsWireDataValid())
	{

		std::cout << output->GetWireDataStr() << std::endl;

	}

	inputB->SetWireData("00000000000000000000000000000101");
	mux1->Update();

	if (output->IsWireDataValid())
	{

		std::cout << output->GetWireDataStr() << std::endl;

	}

	select->SetWireData("01");
	mux1->Update();

	if (output->IsWireDataValid())
	{

		std::cout << output->GetWireDataStr() << std::endl;

	}

	delete inputA;
	delete inputB;
	delete inputC;
	delete inputD;
	delete select;
	delete output;
	delete adda;
	delete mux1;

	return 0;

}