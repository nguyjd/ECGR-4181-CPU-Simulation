#include <iostream>
#include <Adder.h>
#include "Mux2to1.h"
#include "Mux4to1.h"
#include "SignExtend.h"
#include "ZeroExtend.h"
#include "ShiftLeft.h"


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

	Wire* ExInput = new Wire("110111001");
	Wire* ExOutput = new Wire(32);

	SignExtend* signEx = new SignExtend(ExInput, ExOutput);
	ZeroExtend* zeroEx = new ZeroExtend(ExInput, ExOutput);

	if (signEx->IsExtendConfigValid())
	{

		std::cout << "The sign extend is valid" << std::endl;

	}

	if (signEx->IsExtendConfigValid())
	{

		std::cout << "The zero extend is valid" << std::endl;

	}

	std::cout << "SIGN EXTEND" << std::endl;

	if (ExOutput->IsWireDataValid())
	{

		std::cout << ExOutput->GetWireDataStr() << std::endl;

	}

	signEx->Update();

	if (ExOutput->IsWireDataValid())
	{

		std::cout << ExOutput->GetWireDataStr() << std::endl;

	}

	std::cout << "ZERO EXTEND" << std::endl;

	if (ExOutput->IsWireDataValid())
	{

		std::cout << ExOutput->GetWireDataStr() << std::endl;

	}

	zeroEx->Update();

	if (ExOutput->IsWireDataValid())
	{

		std::cout << ExOutput->GetWireDataStr() << std::endl;

	}

	std::cout << "SHIFT LEFT 12" << std::endl;


	Wire* shiftInput = new Wire("00000000000000000000000000000001");
	Wire* shiftoutput = new Wire(32);
	ShiftLeft* shift = new ShiftLeft(shiftInput, shiftoutput, 1);

	if (shift->IsShiftConfigValid())
	{

		std::cout << "The shift left is valid." << std::endl;

	}

	if (shiftoutput->IsWireDataValid())
	{

		std::cout << shiftoutput->GetWireDataStr() << std::endl;

	}

	shift->Update();

	if (shiftoutput->IsWireDataValid())
	{

		std::cout << shiftoutput->GetWireDataStr() << std::endl;

	}

	delete inputA;
	delete inputB;
	delete inputC;
	delete inputD;
	delete select;
	delete output;
	delete adda;
	delete mux1;
	delete ExInput;
	delete ExOutput;
	delete shift;
	delete shiftInput;
	delete shiftoutput;


	return 0;

}